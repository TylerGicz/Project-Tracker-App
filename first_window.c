#include <stdio.h>
#include <windows.h>

/* Project .h files */
#include "error.h"

LRESULT CALLBACK WindowProcessMessage( HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
  static WNDCLASSA window_class = { 0 };                           // creates window class to hold information about the window
  static const char window_class_name[] = "My Window Class";
  window_class.lpszClassName = window_class_name;
  window_class.lpfnWndProc = WindowProcessMessage; //lpfnWndProc = pointer to a function windows will call inorder to handle events(messages)
  window_class.hInstance = hInstance;
  window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
  window_class.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);

  if(RegisterClassA(&window_class) == 0) ERROR_MSG("window class register failure.");
  HWND window_handle = CreateWindowExA(
    0,                            // Extended Window Styles
    window_class_name,            // Window Class Name
    "Learn to Program Windows",   // (TBD)      Window Name
    WS_OVERLAPPEDWINDOW,          // (DWORD)    The sytle of the window
    CW_USEDEFAULT,  // (int)  The initial horizontal position of the window
    CW_USEDEFAULT,  // (int)  The initial vertical position of the window
    CW_USEDEFAULT,  // (int)  The width, in device units, of the window
    CW_USEDEFAULT,  // (int)  The height, in device units, of the window
    NULL,           // (HWND)   A handle to the parent of the window being created
    NULL,           // (HMENU)  A handle to a menu
    hInstance,      // (HINSTANCE)  A handle to the instance of the module to be associated with the window
    NULL            // (LPVOID)     Void pointer to a value to be passed to the window through the CREATESTRUCT structure
  );
  if(window_handle == NULL) { return -1; };
  ShowWindow(window_handle, nCmdShow);

  MSG message = { 0 };
  while(GetMessage(&message, NULL, 0, 0) > 0) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
  
  return 0;
}

LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam) {
  switch(message) {
    case WM_CLOSE: {
      if (MessageBoxA(window_handle, "Would you like to close the application?", "Close Message", MB_YESNO) == IDYES) DestroyWindow(window_handle);
      return 0;
    }
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }
  }
  return DefWindowProc(window_handle, message, wParam, lParam);;
}