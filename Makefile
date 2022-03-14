CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -ggdb

main: main.c K_multip.h
	$(CC) $(CFLAGS) -o main main.c K_multip.c