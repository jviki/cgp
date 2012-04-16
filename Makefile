CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -ggdb3

all: cgp
cgp: cgp.o main.o chromo.o func_gates.o fitness_gates.o rndgen.o alap.o
clean:
	$(RM) *.o
