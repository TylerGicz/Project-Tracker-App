#pragma once

// typedef struct STK STK;

typedef struct {
  STK *msg_stk;
  HWND msg_overlay_hwnd;
} app_instance;

extern app_instance instance;