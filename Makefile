mytar: main.o
	gcc main.o -o mytar

main.o: main.c
	gcc -c main.c -ansi -o main.o