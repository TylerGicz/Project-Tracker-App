#include <stdio.h>
#include <windows.h>
#include <commctrl.h>

/* Project .h files */
#include "error.h"

#define ITEM_1 1
#define ITEM_2 2

LRESULT CALLBACK WindowProcessMessage( HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam);

void AddMenu(HWND window_handle);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
  WNDCLASSA parent_window_class = { 0 };
  parent_window_class.lpszClassName = "My Window Class";
  parent_window_class.lpfnWndProc = WindowProcessMessage;
  parent_window_class.hInstance = hInstance;
  parent_window_class.hCursor = LoadCursorA(NULL, IDC_ARROW);
  if(RegisterClassA(&parent_window_class) == 0) { ERROR_MSG("window class register failure."); }
  HWND parent_window_handle = CreateWindowExA(
    0,                            // Extended Window Styles
    "My Window Class",            // Window Class Name
    "Learn to Program Windows",   // (TBD)      Window Name
    WS_OVERLAPPEDWINDOW,          // (DWORD)    The sytle of the window
    CW_USEDEFAULT,                // (int)  The initial horizontal position of the window
    CW_USEDEFAULT,                // (int)  The initial vertical position of the window
    CW_USEDEFAULT,                // (int)  The width, in device units, of the window
    CW_USEDEFAULT,                // (int)  The height, in device units, of the window
    NULL,                         // (HWND)   A handle to the parent of the window being created
    NULL,                         // (HMENU)  A handle to a menu
    hInstance,                    // (HINSTANCE)  A handle to the instance of the module to be associated with the window
    NULL                          // (LPVOID)     Void pointer to a value to be passed to the window through the CREATESTRUCT structure
  );
  if(parent_window_handle == NULL) { return -1; };
  ShowWindow(parent_window_handle, nCmdShow);

  /*Button*/
  CreateWindowExA(0, "BUTTON", "Button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 100, 100, 30, parent_window_handle, NULL, hInstance, NULL);

  /*Combo Box*/
  CreateWindowExA(0, "COMBOBOX", "Combo", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 100, 100, 200, 200, parent_window_handle, NULL, hInstance, NULL);

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
    case WM_CREATE: {
      AddMenu(window_handle);
      return 0;
    }
    case WM_COMMAND: {
      if(wParam == ITEM_1) { printf("Item 1 was clicked\n"); }
      if(wParam == ITEM_2) { printf("Item 2 was clicked\n"); }
      return 0;
    }
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }
  }
  return DefWindowProc(window_handle, message, wParam, lParam);
}

void AddMenu(HWND window_handle){
  HMENU main_menu = CreateMenu();
  HMENU sub_menu = CreateMenu();
  AppendMenuA(main_menu, MF_STRING, ITEM_1, "Item 1");
  AppendMenuA(main_menu, MF_STRING, ITEM_2, "Item 2");
  AppendMenuA(main_menu, MF_POPUP, (UINT_PTR)sub_menu, "More");
  AppendMenuA(sub_menu, MF_STRING, ITEM_1, "Item 1");
  AppendMenuA(sub_menu, MF_STRING, ITEM_2, "Item 2");
  AppendMenuA(sub_menu, MF_SEPARATOR, 0, NULL);
  AppendMenuA(sub_menu, MF_STRING, ITEM_1, "Item 1");
  AppendMenuA(sub_menu, MF_STRING, ITEM_2, "Item 2");
  SetMenu(window_handle, main_menu);
}