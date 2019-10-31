mytar: main.o encrypted.o
	gcc main.o encrypted.o -o mytar

main.o: main.c
	gcc -c main.c -ansi -o main.o

encrypted.o: encrypted.c encrypted.h
	gcc -c encrypted.c -ansi-o encrypted.o