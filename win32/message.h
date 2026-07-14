#pragma once

#define WC_MSG_OVERLAY "MESSAGE_OVERLAY"
#define WC_MSG_BOX "MESSAGE_BOX"
#define MENU_MSG_OVERLAY 1001
#define MENU_MSG_BOX 1002
#define OK_PRESS 1050

#define MSG_W 500
#define MSG_H 200

#define MSG_HEADER_H 20
#define MSH_HEADER_W MSG_W
#define MSG_BODY_H 130
#define MSG_BODY_W MSG_W
#define MSG_BTN_H 50
#define MSG_BTN_W 100

LRESULT CALLBACK MessageOverlayProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MessageBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void CreateMessage(HWND hwndParent, HINSTANCE hInstance, char* header, char *msg, char *btn_txt);
void ClearMessage(void);
void ResizeMsgOverlay(HWND hwndParent);