/**
 * chromo.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "chromo.h"
#include "chromo_def.h"
#include "func.h"
#include "cgp_config.h"
#include "rndgen.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

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

static
port_t first_port_possible(size_t col)
{
	port_t first_possible = 0;

	if(col == 0)
		first_possible = 0;
	else if(CGP_LBACK > col)
		first_possible = 0;
	else
		first_possible = CGP_INPUTS
			+ (col - 1) * CGP_HEIGHT * func_outputs_max();

	return first_possible;
}

static
port_t last_port_possible(size_t col)
{
	return CGP_INPUTS + col * CGP_HEIGHT * func_outputs_max() - 1;
}

static
port_t port_gen(size_t col)
{
	const size_t first_possible = first_port_possible(col);
	const size_t last_possible  = last_port_possible(col);

	assert(last_possible > first_possible);

	const size_t max = last_possible - first_possible;
	return first_possible + rndgen_range(max);
}

void chromo_gen(struct chromo_t *c)
{
	assert(CGP_LBACK > 0);
	const size_t cells = CGP_WIDTH * CGP_HEIGHT;

	for(size_t i = 0; i < cells; ++i) {
		func_gen(&c->cell[i].f);
		const size_t col = i / CGP_HEIGHT;

		for(size_t j = 0; j < func_inputs_max(); ++j)
			c->cell[i].inputs[j] = port_gen(col);
	}

	for(size_t i = 0; i < CGP_OUTPUTS; ++i)
		c->outputs[i] = port_gen(CGP_WIDTH);
}

void chromo_mut(struct chromo_t *c)
{

}

void chromo_print(FILE *fout, const struct chromo_t *c)
{
	for(size_t i = 0; i < CGP_WIDTH * CGP_HEIGHT; ++i) {
		const struct cell_t *cell = c->cell + i;
		fprintf(fout, "(%zu [%zu, %zu]: ", i, i / CGP_HEIGHT, i % CGP_HEIGHT);

		for(size_t j = 0; j < func_inputs_max(); ++j)
			fprintf(fout, "%zu ", cell->inputs[j]);

		fprintf(fout, "%s) ", func_to_str(cell->f));
	}

	for(size_t j = 0; j < CGP_OUTPUTS; ++j)
		fprintf(fout, "%zu ", c->outputs[j]);
}
