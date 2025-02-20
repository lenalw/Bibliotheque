CC = gcc
flags = -g -Wall -Wextra

all : main mainComp tests

main : main.o entreeSortieLC.o biblioLC.o entreeSortieH.o biblioH.o
	$(CC) $(flags) -o main main.o entreeSortieLC.o biblioLC.o entreeSortieH.o biblioH.o -lm

mainComp : mainComp.o entreeSortieLC.o biblioLC.o entreeSortieH.o biblioH.o
	$(CC) $(flags) -o mainComp mainComp.o entreeSortieLC.o biblioLC.o entreeSortieH.o biblioH.o -lm

main.o : main.c entreeSortieLC.h biblioLC.h entreeSortieH.h biblioH.h
	$(CC) $(flags) -c main.c

tests : tests.o entreeSortieLC.o biblioLC.o entreeSortieH.o biblioH.o
	$(CC) $(flags) -o tests tests.o entreeSortieLC.o biblioLC.o entreeSortieH.o biblioH.o -lm	

tests.o : tests.c entreeSortieLC.h biblioLC.h entreeSortieH.h biblioH.h
	$(CC) $(flags) -c tests.c

mainComp.o : mainComp.c entreeSortieLC.h biblioLC.h entreeSortieH.h biblioH.h
	$(CC) $(flags) -c mainComp.c

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h
	$(CC) $(flags) -c entreeSortieLC.c
	
biblioLC.o : biblioLC.c biblioLC.h
	$(CC) $(flags) -c biblioLC.c

entreeSortieH.o : entreeSortieH.c entreeSortieH.h
	$(CC) $(flags) -c entreeSortieH.c
	
biblioH.o : biblioH.c biblioH.h
	$(CC) $(flags) -c biblioH.c

clean :
	rm -f *.o main mainComp
