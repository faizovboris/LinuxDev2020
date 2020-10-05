TARGET = show
FLAGS = -O3 -Wall -lncursesw -lncurses
CC = gcc

all: show

show: Show.c
	$(CC) -g $^ -o $@ $(FLAGS)

clean:
	rm -rf *~ *.o show
