#include <stdio.h>
#include <windows.h>
#include "message.h"
#include "stack.h"
#include "instance.h"

LRESULT CALLBACK WindowsProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef struct {
  HINSTANCE G_hInstance;
  HWND G_hwnd;
} G_data;
G_data data;

app_instance instance;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow){
  // TODO: create an init funct...
  instance.msg_stk = initStack();
  instance.msg_overlay_hwnd = NULL;

  WNDCLASSA wc_message_box = { 0 };
  wc_message_box.hInstance = hInstance;
  wc_message_box.lpszClassName = WC_MSG_BOX;
  wc_message_box.lpfnWndProc = MessageBoxProc;
  wc_message_box.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc_message_box.hCursor = LoadCursorA(NULL, IDC_ARROW);
  RegisterClassA(&wc_message_box);

  WNDCLASSA wc_message_overlay = { 0 };
  wc_message_overlay.hInstance = hInstance;
  wc_message_overlay.lpszClassName = WC_MSG_OVERLAY;
  wc_message_overlay.lpfnWndProc = MessageOverlayProc;
  //wc_message_overlay.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wc_message_overlay.hCursor = LoadCursorA(NULL, IDC_HAND);
  RegisterClassA(&wc_message_overlay);
  // TODO: create an init funct...


  WNDCLASSA index_wc = { 0 };
  index_wc.hInstance = hInstance;
  index_wc.lpszClassName = "INDEX";
  index_wc.lpfnWndProc = WindowsProc;
  index_wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
  index_wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  RegisterClassA(&index_wc);

  HWND hwndIndex = CreateWindowExA(
    0,
    "INDEX",
    "First Window",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL
  );
  data.G_hInstance = hInstance;
  data.G_hwnd = hwndIndex;
  ShowWindow(hwndIndex, nCmdShow);
  CreateMessage(data.G_hwnd, data.G_hInstance, "Header1", "This is the text within the first box", "Button Text");
  CreateMessage(data.G_hwnd, data.G_hInstance, "Header2", "This is the text within the second box", "Button Text");
  UpdateWindow(hwndIndex);

  MSG msg = { 0 };
  while(GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}

LRESULT CALLBACK WindowsProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
  switch(msg) {
    case WM_SIZE: {
      if(instance.msg_overlay_hwnd) ResizeMsgOverlay(hwnd);
      return 0;
    }
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }
    default: return DefWindowProcA(hwnd, msg, wParam, lParam);
  }
}



