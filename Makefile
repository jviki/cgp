CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

all: cgp
cgp: cgp.o main.o chromo.o func_gates.o fitness_gates.o rndgen.o alap.o
clean:
	$(RM) *.o
