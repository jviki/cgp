CC = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic -O2
CFLAGS += -Wno-unknown-pragmas -fopenmp
LDFLAGS = -lm -fopenmp

OBJ = cgp.o main.o chromo.o func_gates.o fitness_gates.o rndgen.o alap.o bitgen.o

all: cgp
cgp: $(OBJ) cgp_config.h

bitgen-tool: bitgen.o bitgen-tool.o
chromo-tool: chromo.o chromo-tool.o func_gates.o rndgen.o
fitness-tool: fitness-tool.o chromo.o fitness_gates.o func_gates.o rndgen.o alap.o bitgen.o
mut-tool: mut-tool.o chromo.o func_gates.o rndgen.o

clean:
	$(RM) *.o
distclean: clean
	$(RM) bitgen-tool chromo-tool fitness-tool mut-tool cgp
