FLAGS = -ansi -Wall -pedantic

mymat: mymat.o mat.o input.o
	gcc -g $(FLAGS) mymat.o mat.o input.o -o mymat 
mymat.o: mymat.c
	gcc -c $(FLAGS) mymat.c -o mymat.o 
mat.o: mat.c
	gcc -c $(FLAGS) mat.c -o mat.o
input.o: input.c
	gcc -c $(FLAGS) input.c -o input.o