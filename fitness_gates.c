/**
 * fitness_gates.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "fitness.h"
#include "chromo_def.h"
#include "cgp_config.h"
#include "alap.h"
#include "bitgen.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void eval_fenotype(struct cell_t *cells, uint64_t *inputs, uint64_t *outputs)
{
	assert(CGP_INPUTS >= CGP_OUTPUTS);

	memcpy(outputs, inputs, CGP_OUTPUTS * sizeof(uint64_t));
}

int fitness_compute(const struct chromo_t *c, fitness_t *value)
{
	assert(CGP_INPUTS >= CGP_OUTPUTS);

	struct bitgen_t bitgen;
	if(bitgen_init(&bitgen, CGP_INPUTS))
		return 1;

	struct cell_t *cells = chromo_alap(c);
	uint64_t inputs[CGP_INPUTS];
	uint64_t sorted[CGP_INPUTS];
	uint64_t outputs[CGP_OUTPUTS];
	size_t incorrect = 0;

	while(bitgen_next(&bitgen, inputs)) {
		eval_fenotype(cells, inputs, outputs);
		bitgen_sort(inputs, sorted, CGP_INPUTS);

		for(size_t i = 0; i < CGP_OUTPUTS; ++i) {
			if(outputs[i] != sorted[i])
				incorrect += 1;
		}
	}

	*value = incorrect;
	bitgen_fini(&bitgen);
	return 0;
}

int fitness_isbest(fitness_t f)
{
	return f == 0;
}
