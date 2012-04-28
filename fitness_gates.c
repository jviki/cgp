/**
 * fitness_gates.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "fitness.h"
#include "chromo_def.h"
#include "cgp_config.h"
#include "alap.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int fitness_compute(const struct chromo_t *c, fitness_t *value)
{
	struct cell_t *cells = chromo_alap(c);
	uint64_t inputs[CGP_INPUTS];
	uint64_t outputs[CGP_OUTPUTS];
	size_t incorrect = 0;

//	size_t i = 0;
//	while(gen_inputs(inputs, CGP_INPUTS, i++)) {
//		eval_inputs(inputs, outputs, cells);
//		expected_outputs(outputs);
//	}

	*value = incorrect;
	return 0;
}

int fitness_isbest(fitness_t f)
{
	return f == 0;
}
