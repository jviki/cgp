CC = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic
LDFLAGS = -lm

ifdef DEBUG
CFLAGS += -ggdb3
CFLAGS += -DLOG_MASK=1
else
CFLAGS += -O2
endif

ifdef OPENMP
CFLAGS += -fopenmp -Wno-unknown-pragmas
LDFLAGS += -fopenmp
endif

OBJ = cgp.o main.o chromo.o $(FUNC_MOD) $(FITNESS) fenotype64.o rndgen.o alap.o bitgen.o ports_set.o
FUNC_MOD ?= func_swap.o
FITNESS  ?= fitness_bits64.o

all: cgp
cgp: $(OBJ) cgp_config.h

bitgen-tool: bitgen.o bitgen-tool.o
chromo-tool: chromo.o chromo-tool.o $(FUNC_MOD) rndgen.o
fitness-tool: fitness-tool.o chromo.o $(FITNESS) fenotype64.o $(FUNC_MOD) rndgen.o alap.o bitgen.o ports_set.o
mut-tool: mut-tool.o chromo.o $(FUNC_MOD) rndgen.o
eval-tool: eval-tool.o chromo.o $(FUNC_MOD) fenotype64.o rndgen.o alap.o ports_set.o
alap-tool: alap-tool.o chromo.o alap.o $(FUNC_MOD) rndgen.o ports_set.o

clean:
	$(RM) *.o
distclean: clean
	$(RM) bitgen-tool chromo-tool fitness-tool mut-tool cgp
