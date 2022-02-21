CFLAGS=-Wall -Wextra -Werror -std=c11 -pedantic -ggdb

heap: karatsuba_s_multiplication.c
	$(CC) $(CFLAGS) -o out karatsuba_s_multiplication.c