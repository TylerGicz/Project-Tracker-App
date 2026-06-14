#ifndef ERROR_H
#define ERROR_H

void printError(const char *message);

#define ERROR_MSG(message) printError(message)

#endif