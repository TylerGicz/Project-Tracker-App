#include <stdio.h>
#include <windows.h>
#include <Commctrl.h>
#include "message.h"
#include "stack.h"
#include "instance.h"

LRESULT CALLBACK MessageOverlayProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
  switch(msg){
    case WM_LBUTTONDOWN: {
      ClearMessage();
      return 0;
    }
    default: return DefWindowProcA(hwnd, msg, wParam, lParam);
  }
}

LRESULT CALLBACK MessageBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
  switch(msg) {
    case WM_COMMAND: {
      if (LOWORD(wParam) == OK_PRESS) ClearMessage();
      return 0;
    }
    default: return DefWindowProcA(hwnd, msg, wParam, lParam);
  }
}

void CreateMessage(HWND hwndParent, HINSTANCE hInstance, char* header, char *msg, char *btn_txt) {
  msg = msg ? msg : "Undefined";
  btn_txt = btn_txt ? btn_txt : "OK";

  // Create an overlay only if the message stk is empty
  if(isEmpty(instance.msg_stk)) {
    instance.msg_overlay_hwnd = CreateWindowExA(
      0,
      WC_MSG_OVERLAY,
      "Message Overlay",
      WS_CHILD | WS_VISIBLE,
      0,
      0,
      0,
      0,
      hwndParent,
      (HMENU) MENU_MSG_OVERLAY,
      hInstance,
      NULL
    );
  }
  
  HWND hwndMsgbox = CreateWindowExA(
    0,
    WC_MSG_BOX,
    "Message Box",
    WS_CHILD | WS_VISIBLE | WS_BORDER,
    0,
    0,
    MSG_W,
    MSG_H,
    instance.msg_overlay_hwnd,
    (HMENU) MENU_MSG_BOX,
    hInstance,
    NULL
  );
  push((void *)hwndMsgbox, instance.msg_stk);
  CreateWindowExA( // Create Header Window
    0,
    "STATIC",
    header,
    WS_CHILD | WS_VISIBLE | SS_CENTER,
    0,
    0,
    MSG_W,
    MSG_HEADER_H,
    hwndMsgbox,
    NULL,
    hInstance,
    NULL
  );
  CreateWindowExA( // Create Body Window
    0,
    "STATIC",
    msg,
    WS_CHILD | WS_VISIBLE | SS_CENTER,
    0,
    MSG_HEADER_H,
    MSG_W,
    MSG_BODY_H,
    hwndMsgbox,
    NULL,
    hInstance,
    NULL
  );
  CreateWindowExA( // Create Button Window
    0,
    "BUTTON",
    btn_txt,
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
    (MSG_W - MSG_BTN_W) / 2,
    MSG_HEADER_H + MSG_BODY_H,
    MSG_BTN_W,
    MSG_BTN_H,
    hwndMsgbox,
    (HMENU) OK_PRESS,
    hInstance,
    NULL
  );
  ResizeMsgOverlay(hwndParent);
}

void ClearMessage(){
  if(isEmpty(instance.msg_stk)) {
    printf("No message found to clear");
    return;
  }
  DestroyWindow((HWND)pop(instance.msg_stk));
  if(isEmpty(instance.msg_stk)) {
    DestroyWindow(instance.msg_overlay_hwnd);
    instance.msg_overlay_hwnd = NULL;
  }
}

void CenterMsgBox(HWND hwndOverlay){
  RECT rcParent;
  GetClientRect(hwndOverlay, &rcParent);
  int x = (rcParent.right - MSG_W) / 2;
  int y = (rcParent.bottom - MSG_H) / 2;
  HWND hwndChild = GetWindow(hwndOverlay, GW_CHILD);
  while(hwndChild) {
    HWND next = GetWindow(hwndChild, GW_HWNDNEXT);
    SetWindowPos(hwndChild, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW);
    hwndChild = next;
  }
}

void ResizeMsgOverlay(HWND hwndMain){
  HWND hwndOverlay = instance.msg_overlay_hwnd;
  RECT rcParent;
  GetClientRect(hwndMain, &rcParent);
  SetWindowPos(hwndOverlay, NULL, 0, 0, rcParent.right, rcParent.bottom, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW);
  CenterMsgBox(hwndOverlay);
  RedrawWindow(hwndOverlay, NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN | RDW_ERASE );
}