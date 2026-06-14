#include <stdio.h>
#include <windows.h>
#include "error.h"

void printError(const char *message)
{
    printf("ERROR: %s\n", message);
    PostQuitMessage(0);
}