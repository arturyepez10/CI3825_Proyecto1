mytar: main.o encrypted.o packing.o
	gcc main.o encrypted.o packing.o -o mytar

main.o: main.c
	gcc -c main.c -ansi -o main.o

encrypted.o: encrypted.c encrypted.h
	gcc -c encrypted.c -ansi-o encrypted.o

packing.o: packing.c packing.h
	gcc -c packing.c -ansi -o packing.o