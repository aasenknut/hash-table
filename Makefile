CFLAGS=-Wall -Wextra -Werror -ggdb

hash: main.c
	gcc $(CFLAGS) -o main main.c && ./main
