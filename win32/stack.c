#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

STK* initStack(){
  STK *stk = NULL;
  stk = malloc(sizeof(STK)); 
  if (stk == NULL) return NULL;
  stk->top = NULL;
  return stk;
}

void push(void* data, STK *STK){
  // Create a new node and init with data
  NODE *new_node = malloc(sizeof(NODE));
  if (new_node == NULL) return;
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = NULL;
  
  if(STK->top != NULL) {
    STK->top->next = new_node;  // set the old top node's 'next' entry equal to our new node
    new_node->prev = STK->top;  // set the new node's 'prev' entry equal to the old top node 
  }
  STK->top = new_node;          // update top tracker
}

void* pop(STK *stk){
  NODE* top = stk->top;
  if(top == NULL) return ISEMPTY;     // TODO: create an ERROR macro to end program gracefully
  void* data = top->data; 
  NODE *prev = top->prev;
  if(prev != NULL) prev->next = NULL;
  stk->top = prev; 
  free(top);
  return data;
}

void* peek(STK *stk){
  NODE* top = stk->top;
  if(top == NULL) return ISEMPTY;   // TODO: create an ERROR macro to end program gracefully
  return top->data;
}

int isEmpty(STK *stk){
  return (peek(stk) == ISEMPTY) ?  1 : 0;
}

// int main(){ // TESTING
//   STK *my_stack = initStack();
//   int data_1 = 1;
//   int data_2 = 2;
//   int data_3 = 3;
//   push(&data_1, my_stack);
//   push(&data_2, my_stack);
//   push(&data_3, my_stack);

//   if(peek(my_stack) != ISEMPTY)
//     printf("The value from peek is: %d\n", *(int*)peek(my_stack));
//   while(peek(my_stack) != ISEMPTY)
//     printf("The value is: %d\n", *(int*)pop(my_stack));
//   if(isEmpty(my_stack)) printf("The stack is empty");
// }