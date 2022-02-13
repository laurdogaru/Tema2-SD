all : minimax2.c

build : minimax2.c
	gcc -g -Wall -std=c99 minimax2.c -o minimax

clean:
	rm minimax