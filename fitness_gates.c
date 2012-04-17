/**
 * fitness_gates.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "fitness.h"
#include "chromo_def.h"
#include "alap.h"
#include <stdio.h>

int fitness_compute(const struct chromo_t *c, fitness_t *value)
{
	struct cell_t *cells = chromo_alap(c);

	for(; cells != NULL; cells = cells->next) {
		fprintf(stderr, "%s/%zu (", func_to_str(cells->f), cells->id);

		for(size_t i = 0; i < func_inputs_max(); ++i) {
			fprintf(stderr, "%zu", cells->inputs[i]);
			if(i + 1 == func_inputs_max())
				fprintf(stderr, ")");
			else
				fprintf(stderr, " ");
		}

		if(cells->next != NULL)
			fprintf(stderr, " :: ");
	}

	fprintf(stderr, "\n");
	*value = 0;
	return 0;
}

int fitness_isbest(fitness_t f)
{
	return f == 0;
}
