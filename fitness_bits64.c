/**
 * fitness_gates.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "fitness.h"
#include "chromo_def.h"
#include "cgp_config.h"
#include "alap.h"
#include "bitgen.h"
#include "fenotype64.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

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

static
size_t count_cell_list(const struct cell_t *c)
{
	size_t size;
	const struct cell_t *curr;

	for(size = 0, curr = c; curr != NULL; curr = curr->next, size += 1)
		/* no stuff */;

	return size;
}

int fitness_compute(const struct chromo_t *c, fitness_t *value)
{
	assert(CGP_INPUTS >= CGP_OUTPUTS);
	static const size_t max_count = CGP_WIDTH * CGP_HEIGHT;

	struct bitgen_t bitgen;
	if(bitgen_init(&bitgen, CGP_INPUTS))
		return 1;

	struct cell_t *cells = chromo_alap(c);
	uint64_t inputs[CGP_INPUTS];
	uint64_t sorted[CGP_INPUTS];
	uint64_t outputs[CGP_OUTPUTS];
	size_t incorrect = 0;
	uint64_t mask = 0xFFFFFFFFFFFFFFFF;

	while(bitgen_next(&bitgen, inputs)) {
		eval_fenotype(cells, c->outputs, inputs, outputs);
		bitgen_sort(inputs, sorted, CGP_INPUTS);

		if(!bitgen_has_next(&bitgen))
			mask = CGP_OUTPUTS >= 6? 0xFFFFFFFFFFFFFFFF
			     : (((uint64_t) 1) << (1 << CGP_OUTPUTS)) - 1;

		for(size_t i = 0; i < CGP_OUTPUTS; ++i) {
			const uint64_t tmp = outputs[i] ^ sorted[i];
			incorrect += count_ones(tmp & mask);
		}
	}

	if(incorrect == 0)
		*value = max_count - count_cell_list(cells);
	else
		*value = incorrect + max_count;

	bitgen_fini(&bitgen);
	return 0;
}

int fitness_isacceptable(fitness_t f)
{
	static const size_t max_count = CGP_WIDTH * CGP_HEIGHT;
	return f <= max_count;
}
