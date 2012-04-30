/**
 * alap-tool.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "chromo.h"
#include "chromo_def.h"
#include "alap.h"
#include "cgp_config.h"
#include <stdio.h>
#include <stdlib.h>

int cell_in_list(const struct cell_t *list, const struct cell_t *cell)
{
	const struct cell_t *curr;

	for(curr = list; curr != NULL; curr = curr->next) {
		if(curr == cell)
			return 1;
	}

	return 0;
}

void print_cell(const struct cell_t *cell)
{
	printf("%d ", cell->f);

	for(size_t j = 0; j < func_inputs_max(); ++j)
		printf("%zu ", cell->inputs[j]);
}

void plumb_cell(const struct cell_t *cell)
{
	printf("-1 ");

	for(size_t j = 0; j < func_inputs_max(); ++j)
		printf("-1 ");
}

void print_chromo_without(const struct chromo_t *c, const struct cell_t *list)
{
	printf("%d %d ", CGP_WIDTH, CGP_HEIGHT);
	printf("%d %d ", CGP_INPUTS, CGP_OUTPUTS);
	printf("%zu %zu ", func_inputs_max(), func_outputs_max());

	for(size_t i = 0; i < CGP_WIDTH * CGP_HEIGHT; ++i) {
		const struct cell_t *cell = c->cell + i;

		if(cell_in_list(list, cell))
			print_cell(cell);
		else
			plumb_cell(cell);
	}

	for(size_t j = 0; j < CGP_OUTPUTS; ++j)
		printf("%zu ", c->outputs[j]);
}

int main(int argc, char **argv)
{
	struct chromo_t *c = chromo_alloc(1);
	if(c == NULL) {
		fprintf(stderr, "Chromosome allocation failed\n");
		return 1;
	}

	int err;
	if((err = chromo_parse(stdin, c))) {
		fprintf(stderr, "Can not parse the chromosome: %d\n", err);
		return 2;
	}

	struct cell_t *alap = chromo_alap(c);
	print_chromo_without(c, alap);
	printf("\n");

	struct cell_t *curr;
	size_t count = 0;

	for(curr = alap; curr != NULL; curr = curr->next) {
		printf("[%zu ", curr->id);
		print_cell(curr);
		printf("\b] ");
		count += 1;
	}
	printf("\nCells: %zu\n", count);

	chromo_free(c);
	return 0;
}
