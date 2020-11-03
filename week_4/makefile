CFLAGS=-Wall -Wextra  -Wfloat-equal -pedantic  -ansi -lm -fsanitize=undefined -fsanitize=address -g3 -std=c90 -O2
CC=clang
$(MAKECMDGOALS) : $(MAKECMDGOALS).c
	$(CC)  $(MAKECMDGOALS).c $(CFLAGS) -o $(MAKECMDGOALS)
