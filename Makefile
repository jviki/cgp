CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

all: cgp.o main.o chromo_bitonic.o
clean:
	$(RM) *.o
