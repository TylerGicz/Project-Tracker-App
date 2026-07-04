#include <stdio.h>
#include <windows.h>
#include <Commctrl.h>
#include "message.h"
#include "stack.h"
#include "instance.h"

LRESULT CALLBACK MessageOverlayProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
  return DefWindowProcA(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK MessageBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
  switch(msg) {
    case WM_COMMAND: {
      if (LOWORD(wParam) == OK_PRESS) {
        ClearMessage();
        return 0;
      }
      break;
    }
    default: {
      return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
  }
  return 0;
}

/** CreateMessage generates a windows which presents the user with a message with a okay button to close
 *  Features:
 *  OK button with custom text (default 'OK')
 *  Custom placement (defualt centered about the main window)
 */
void CreateMessage(HWND hwndParent, HINSTANCE hInstance, char *msg, char *btn_txt) {
  msg = msg ? msg : "Undefined";
  btn_txt = btn_txt ? btn_txt : "OK";

  RECT rcParent;
  GetClientRect(hwndParent, &rcParent);
  int x = (rcParent.right - rcParent.left - 500) / 2;
  int y = (rcParent.bottom - rcParent.top - 200) / 2;

  int box_width = 500;
  int box_height = 200;

  // Create an overlay only if the message stk is empty
  if(isEmpty(instance.msg_stk)) {
    instance.msg_overlay_hwnd = CreateWindowExA(
      0,
      WC_MSG_OVERLAY,
      "Message Overlay",
      WS_CHILD | WS_VISIBLE,
      0,
      0,
      rcParent.right,
      rcParent.bottom,
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
    x,
    y,
    500,
    200,
    instance.msg_overlay_hwnd,
    (HMENU) MENU_MSG_BOX,
    hInstance,
    NULL
  );
  push((void *)hwndMsgbox, instance.msg_stk);
  HWND hwndEdit = CreateWindowExA( 0, "EDIT", msg, WS_CHILD | WS_VISIBLE | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL | ES_CENTER, 0, 0, 500, 150, hwndMsgbox, NULL, hInstance, NULL);
  CreateWindowExA(0, "BUTTON", btn_txt, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 200, 150, 100, 50, hwndMsgbox, (HMENU) OK_PRESS, hInstance, NULL);
}

void ClearMessage(){
  if(isEmpty(instance.msg_stk)) {
    printf("No message found to clear");
    return;
  }
  DestroyWindow((HWND)pop(instance.msg_stk));
  if(isEmpty(instance.msg_stk)) DestroyWindow(instance.msg_overlay_hwnd);
}
