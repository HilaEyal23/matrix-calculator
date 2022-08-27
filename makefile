FLAGS = -ansi -Wall -pedantic

mymat: main.o mat.o input.o
	gcc -g $(FLAGS) main.o mat.o input.o -o mymat 
maint.o: main.c
	gcc -c $(FLAGS) main.c -o main.o 
mat.o: mat.c
	gcc -c $(FLAGS) mat.c -o mat.o
input.o: input.c
	gcc -c $(FLAGS) input.c -o input.o
