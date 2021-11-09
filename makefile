all: pwcheck.c
	gcc -g -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck
