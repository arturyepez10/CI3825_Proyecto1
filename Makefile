mytar: main.o encrypted.o packing.o
	gcc main.o encrypted.o packing.o -o mytar

main.o: main.c
	gcc -c main.c -ansi -Wpedantic -o main.o

encrypted.o: encrypted.c encrypted.h
	gcc -c encrypted.c -ansi -Wpedantic -o encrypted.o

packing.o: packing.c packing.h
	gcc -c packing.c -ansi -Wpedantic -o packing.o