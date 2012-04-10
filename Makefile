CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

all: cgp.o main.o
clean:
	$(RM) *.o
