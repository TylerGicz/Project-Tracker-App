#pragma once

#define ISEMPTY NULL

typedef struct NODE{
  void* data;
  struct NODE *next;
  struct NODE *prev;
} NODE;

typedef struct STK{
  NODE* top;
} STK;

STK* initStack(void);
void push(void* data, STK *STK);
void* pop(STK *stk);
void* peek(STK *stk);
int isEmpty(STK *stk);