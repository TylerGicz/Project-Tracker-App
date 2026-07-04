# mingw32-make

app : main.o message.o stack.o
	cc -o app main.o message.o stack.o -lcomctl32 -lgdi32 -luser32

main.o : main.c message.h stack.h instance.h
	cc -c main.c

message.o : message.c stack.h instance.h
	cc -c message.c

stack.o : stack.c
	cc -c stack.c

clean :
	del app main.o message.o stack.o