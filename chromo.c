/**
 * chromo.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "chromo.h"
#include "chromo_def.h"
#include "func.h"
#include "cgp_config.h"
#include <stdlib.h>
#include <stdio.h>

struct chromo_t *chromo_at(struct chromo_t *list, size_t i)
{
	return list + i;
}

static
struct chromo_t *impl_chromos_alloc(size_t count)
{
	return (struct chromo_t *) malloc(count * sizeof(struct chromo_t));
}

static
struct cell_t *impl_cells_alloc(size_t count)
{
	const size_t cells = CGP_WIDTH * CGP_HEIGHT;
	return (struct cell_t *) malloc(count * cells * sizeof(struct cell_t));
}

static
port_t *impl_inputs_alloc(size_t count)
{
	const size_t cells = CGP_WIDTH * CGP_HEIGHT;
	const size_t inputs = cells * func_inputs_max();
	return (port_t *) malloc(count * inputs * sizeof(port_t));
}

static
port_t *impl_outputs_alloc(size_t count)
{
	return (port_t *) malloc(count * CGP_OUTPUTS * sizeof(port_t));
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

		for(size_t j = 0; j < func_inputs_max(); ++j)
			fprintf(fout, "%d ", cell->inputs[j]);

		fprintf(fout, "%s ", func_to_str(cell->f));
	}

	for(size_t j = 0; j < CGP_OUTPUTS; ++j)
		fprintf(fout, "%d ", c->outputs[j]);
}
