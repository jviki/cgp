/**
 * fenotype64.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "fitness.h"
#include "chromo_def.h"
#include "cgp_config.h"
#include "fenotype64.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void eval_fenotype(const struct cell_t *cells, const port_t *outports,
		const uint64_t *inputs, uint64_t *outputs)
{
	assert(CGP_INPUTS >= CGP_OUTPUTS);
	uint64_t op[func_inputs_max()];
	uint64_t cache[CGP_INPUTS
		+ (func_inputs_max() * CGP_WIDTH * CGP_HEIGHT)];

	memset(cache, 0, sizeof(cache));
	memcpy(cache, inputs, sizeof(uint64_t) * CGP_INPUTS);

	const struct cell_t *curr;
	for(curr = cells; curr != NULL; curr = curr->next) {
		for(size_t i = 0; i < func_inputs(curr->f); ++i)
			op[i] = cache[curr->inputs[i]];

		size_t first;
		size_t notused;
		cell_outputs(curr, &first, &notused);

		func_eval64(curr->f, op, cache + first);
	}

	for(size_t i = 0; i < CGP_OUTPUTS; ++i)
		outputs[i] = cache[outports[i]];
}
