mytar: main.o encrypted.o look.o
	gcc main.o encrypted.o look.o -o mytar

main.o: main.c
	gcc -c main.c -ansi -Wpedantic -o main.o

encrypted.o: encrypted.c encrypted.h
	gcc -c encrypted.c -ansi -Wpedantic -o encrypted.o

look.o: look.c look.h
	gcc -c look.c -ansi -Wpedantic -o look.o