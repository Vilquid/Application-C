main: DataProcess.o main.o
	gcc -o main DataProcess.o main.o

DataProcess.o: DataProcess.c
	gcc -o DataProcess.o -c DataProcess.c

main.o: main.c DataProcess.h
	gcc -o main.o -c main.c
