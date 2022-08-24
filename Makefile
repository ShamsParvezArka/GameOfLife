CC = gcc
CFlags = -Wall

gol: main.c
	$(CC) $(CFlags) main.c -o gol
