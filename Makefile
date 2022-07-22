CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -ggdb

main: main.c
	$(CC) $(CFLAGS) -o main main.c

km: karatsuba-s-multiplication.c
	$(CC) $(CFLAGS) -o out karatsuba-s-multiplication.c

test: test.c
	$(CC) -o test test.c