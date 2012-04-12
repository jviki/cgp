/**
 * chromo.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "chromo.h"
#include "func.h"
#include "cgp_config.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Id of connected port.
 */
typedef int port_t;

/**
 * Representation of one cell in the CGP matrix.
 */
struct cell_t {
	enum func_t f;
	port_t *inputs;
};

/**
 * Chromosome for bitonic sorter.
 */
struct chromo_t {
	struct cell_t *cell;
	port_t *outputs;
};

struct chromo_t *chromo_at(struct chromo_t *list, size_t i)
{
	return list + i;
}

struct chromo_t *chromo_alloc(size_t count)
{
	struct chromo_t *c = NULL;
	return c;
}

void chromo_free(struct chromo_t *c)
{
	if(c != NULL) {
		free(c);
	}
}

void chromo_gen(struct chromo_t *c)
{

}

void chromo_mut(struct chromo_t *c)
{

}

void chromo_print(FILE *fout, const struct chromo_t *c)
{
	for(size_t i = 0; i < CGP_WIDTH * CGP_HEIGHT; ++i) {
		const struct cell_t *cell = c->cell + i;

		for(size_t j = 0; j < FUNC_INPUTS; ++j)
			fprintf(fout, "%d ", cell->inputs[j]);

		fprintf(fout, "%s ", func_to_str(cell->f));
	}

	for(size_t j = 0; j < CGP_OUTPUTS; ++j)
		fprintf(fout, "%d ", c->outputs[j]);
}
