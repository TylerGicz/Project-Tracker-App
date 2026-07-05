#pragma once

#define WC_MSG_OVERLAY "MESSAGE_OVERLAY"
#define WC_MSG_BOX "MESSAGE_BOX"
#define MENU_MSG_OVERLAY 1001
#define MENU_MSG_BOX 1002
#define OK_PRESS 1050

#define MSG_WIDTH 500
#define MSG_HEIGHT 200

LRESULT CALLBACK MessageOverlayProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MessageBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void CreateMessage(HWND hwndParent, HINSTANCE hInstance, char *msg, char *btn_txt);
void ClearMessage(void);
void ResizeMsgOverlay(HWND hwndParent);