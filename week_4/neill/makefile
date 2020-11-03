CFLAGS=-Wall -Wextra  -Wfloat-equal -pedantic  -ansi -lm -fsanitize=undefined -fsanitize=address -g3 -std=c90
CC=clang

$(MAKECMDGOALS) : $(MAKECMDGOALS).c
	$(CC)  $(MAKECMDGOALS).c neillsimplescreen.c $(CFLAGS) -o $(MAKECMDGOALS)
