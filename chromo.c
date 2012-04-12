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
#include <string.h>

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
	const size_t cells = CGP_WIDTH * CGP_HEIGHT;
	const size_t inputs = cells * func_inputs_max();

	if(count == 0)
		return NULL;

	struct chromo_t *c = impl_chromos_alloc(count);
	struct cell_t *all_cells = impl_cells_alloc(count);
	port_t *all_inputs = impl_inputs_alloc(count);
	port_t *all_outputs = impl_outputs_alloc(count);

	for(size_t i = 0; i < count; ++i) {
		c[i].cell = all_cells + (i * cells);
		c[i].outputs = all_outputs + (i * CGP_OUTPUTS);

		for(size_t j = 0; j < cells; ++j)
			c[i].cell[j].inputs = all_inputs + (i * inputs) + (j * func_inputs_max());
	}

	return c;
}

void chromo_free(struct chromo_t *c)
{
	if(c != NULL) {
		free(c->cell->inputs);
		free(c->cell);
		free(c->outputs);
		free(c);
	}
}

void chromo_gen(struct chromo_t *c)
{
	const size_t cells = CGP_WIDTH * CGP_HEIGHT;

	for(size_t i = 0; i < cells; ++i) {
		c->cell[i].f = 0;
		memset(c->cell[i].inputs, 0, sizeof(port_t) * func_inputs_max());
	}

	memset(c->outputs, 0, sizeof(port_t) * CGP_OUTPUTS);
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
