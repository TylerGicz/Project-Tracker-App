CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wno-unused-parameter

LDLIBS = -lgdi32 -luser32

TARGET = first_window.exe

OBJECTS = first_window.o error.o

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDLIBS)

first_window.o: first_window.c
	$(CC) $(CFLAGS) -c first_window.c

error.o: error.c
	$(CC) $(CFLAGS) -c error.c

clean:
	-del /Q /F $(TARGET) *.o >NUL 2>&1