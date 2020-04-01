./pac:main.o pac.o ghost.o func.o
	gcc -o pac main.o pac.o ghost.o func.o -lncurses
main.o:main.c pac.h ghost.h func.h
	gcc -c main.c 
pac.o:pac.c pac.h ghost.h func.h
	gcc -c pac.c 
ghost.o:ghost.c pac.h ghost.h func.h
	gcc -c ghost.c 
func.o:func.c pac.h ghost.h func.h
	gcc -c func.c 
