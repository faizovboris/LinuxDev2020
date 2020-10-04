TARGET = main
FLAGS = -O3 -Wall -lncursesw -lncurses
CC = gcc

all: main

main: main.c
	$(CC) -g $^ -o $@ $(FLAGS)

clean:
	rm -rf *~ *.o main
