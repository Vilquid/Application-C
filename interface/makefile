main : interface.o 
	gcc -o interface interface.o ../Lib/libisentlib.a -lm -lglut -lGL -lX11

main.o : interface.c
	gcc -g -Wall -c interface.c
	
