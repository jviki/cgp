CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

all: cgp
cgp: cgp.o main.o chromo_bitonic.o
clean:
	$(RM) *.o
