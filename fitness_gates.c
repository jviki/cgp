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

static
void eval_fenotype(struct cell_t *cells, port_t *outports,
		uint64_t *inputs, uint64_t *outputs)
{
	assert(CGP_INPUTS >= CGP_OUTPUTS);
	uint64_t op[func_inputs_max()];
	uint64_t cache[CGP_INPUTS
		+ (func_inputs_max() * CGP_WIDTH * CGP_HEIGHT)];

	memcpy(cache, inputs, sizeof(uint64_t) * CGP_INPUTS);

	struct cell_t *curr;
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

// See http://gurmeet.net/puzzles/fast-bit-counting-routines/
static inline
size_t dense_ones(uint64_t n)
{
	size_t count = 8 * sizeof(uint64_t);
	n ^= (uint64_t) -1;

	while(n) {
		count--;
		n &= n - 1;
	}

	return count;
}

static
size_t count_ones(uint64_t bits)
{
#if defined(__GNUC__)
	return __builtin_popcountll(bits);
#else
	return dense_ones(bits);
#endif
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
		eval_fenotype(cells, c->outputs, inputs, outputs);
		bitgen_sort(inputs, sorted, CGP_INPUTS);

		for(size_t i = 0; i < CGP_OUTPUTS; ++i) {
			const uint64_t tmp = outputs[i] ^ sorted[i];
			incorrect += count_ones(tmp);
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
