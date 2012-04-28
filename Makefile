CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -ggdb3

all: cgp
cgp: cgp.o main.o chromo.o func_gates.o fitness_gates.o rndgen.o alap.o bitgen.o

bitgen-tool: bitgen.o bitgen-tool.o
chromo-tool: chromo.o chromo-tool.o func_gates.o rndgen.o
fitness-tool: fitness-tool.o chromo.o fitness_gates.o func_gates.o rndgen.o alap.o bitgen.o
mut-tool: mut-tool.o chromo.o func_gates.o rndgen.o

clean:
	$(RM) *.o
