mytar: main.o encrypted.o look.o packing.o unpacking.o
	gcc main.o encrypted.o look.o packing.o unpacking.o -o mytar

main.o: main.c
	gcc -c main.c -ansi -Wpedantic -o main.o

encrypted.o: encrypted.c encrypted.h
	gcc -c encrypted.c -ansi -Wpedantic -o encrypted.o

look.o: look.c look.h
	gcc -c look.c -ansi -Wpedantic -o look.o

packing.o: packing.c packing.h
	gcc -c packing.c -ansi -Wpedantic -o packing.o

unpacking.o: unpacking.c unpacking.h
	gcc -c unpacking.c -ansi -Wpedantic -o unpacking.o