CFLAGS=-Wall -Wextra  -Wfloat-equal -pedantic  -ansi -lm -fsanitize=undefined -fsanitize=address -g3 -std=c90 -O2
CC=clang

maze: neillsimplescreen.h maze.c
	$(CC)  maze.c neillsimplescreen.c $(CFLAGS) -o $maze


$(MAKECMDGOALS) : $(MAKECMDGOALS).c
	$(CC)  $(MAKECMDGOALS).c $(CFLAGS) -o $(MAKECMDGOALS)

