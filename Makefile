CC = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic
LDFLAGS = -lm -fopenmp

ifdef DEBUG
CFLAGS += -ggdb3
else
CFLAGS += -O2
endif

ifdef OPENMP
CFLAGS += -fopenmp -Wno-unknown-pragmas
endif

OBJ = cgp.o main.o chromo.o $(FUNC_MOD) fitness_bits64.o fenotype64.o rndgen.o alap.o bitgen.o
FUNC_MOD ?= func_swap.o

all: cgp
cgp: $(OBJ) cgp_config.h

bitgen-tool: bitgen.o bitgen-tool.o
chromo-tool: chromo.o chromo-tool.o $(FUNC_MOD) rndgen.o
fitness-tool: fitness-tool.o chromo.o fitness_bits64.o fenotype64.o $(FUNC_MOD) rndgen.o alap.o bitgen.o
mut-tool: mut-tool.o chromo.o $(FUNC_MOD) rndgen.o
eval-tool: eval-tool.o chromo.o $(FUNC_MOD) fenotype64.o rndgen.o alap.o

clean:
	$(RM) *.o
distclean: clean
	$(RM) bitgen-tool chromo-tool fitness-tool mut-tool cgp
