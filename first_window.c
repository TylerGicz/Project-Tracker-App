#include <windows.h>
#include <stdbool.h>

static bool quit = false;

LRESULT CALLBACK WindowProcessMessage( HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
  static WNDCLASS window_class = { 0 };                           // creates window class to hold information about the window
  static const wchar_t window_class_name[] = L"My Window Class";
  window_class.lpszClassName = (PCSTR)window_class_name;
  window_class.lpfnWndProc = WindowProcessMessage; //lpfnWndProc = pointer to a function windows will call inorder to handle events(messages)
  window_class.hInstance = hInstance;
  window_class.hCursor = LoadCursor(NULL, IDC_ARROW);

  RegisterClass(&window_class);

  HWND window_handle = CreateWindow((PCSTR)window_class_name, "Learn to Program Windows", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  if(window_handle == NULL) { return -1; };

  ShowWindow(window_handle, nCmdShow);

  while(!quit) {
    static MSG message = { 0 };
    while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) { // check fore the next message and remove it from the queue
      TranslateMessage(&message);
      DispatchMessage(&message);
    }
  }
  return 0;
}

LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam) {
  switch(message) {
    case WM_QUIT:
    case WM_DESTROY: {
      quit = true;
    } break;
    default: {
      return DefWindowProc(window_handle, message, wParam, lParam);
    } break;
  }
  return 0;
}