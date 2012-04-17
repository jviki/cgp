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

static
int is_odd(size_t i)
{
	return i % 2 == 1;
}

/**
 * Generates `count` inputs.
 */
static
int gen_inputs(uint64_t *inputs, size_t count, size_t i)
{
	assert(count > 0);
	const size_t k = ((size_t) 0x01) << (count - 7);

	switch(count) {
	case 1:
		inputs[0] = 0x00000002;
		return 0;
	case 2:
		inputs[0] = 0x0000000C;
		inputs[1] = 0x0000000A;
		return 0;
	case 3:
		inputs[0] = 0x000000F0;
		inputs[1] = 0x000000CC;
		inputs[2] = 0x000000AA;
		return 0;
	case 4:
		inputs[0] = 0x0000FF00;
		inputs[1] = 0x0000F0F0;
		inputs[2] = 0x0000CCCC;
		inputs[3] = 0x0000AAAA;
		return 0;
	case 5:
		inputs[0] = 0xFFFF0000;
		inputs[1] = 0xFF00FF00;
		inputs[2] = 0xF0F0F0F0;
		inputs[3] = 0xCCCCCCCC;
		inputs[4] = 0xAAAAAAAA;
		return 0;
	case 6:
		inputs[0] = 0xFFFFFFFF00000000;
		inputs[1] = 0xFFFF0000FFFF0000;
		inputs[2] = 0xFF00FF00FF00FF00;
		inputs[3] = 0xF0F0F0F0F0F0F0F0;
		inputs[4] = 0xCCCCCCCCCCCCCCCC;
		inputs[5] = 0xAAAAAAAAAAAAAAAA;
		return 0;
//	case 7:
//		inputs[0] = is_odd(i)? 0x0000000000000000 : 0xFFFFFFFFFFFFFFFF;
//		gen_inputs(inputs + 1, 6, i);
//		return i < 2;
//	case 8:
//		inputs[0] = is_odd(i / 2)? 0x0000000000000000 : 0xFFFFFFFFFFFFFFFF;
//		gen_inputs(inputs + 2, 7, i);
//		return i < 4;
	default:
		inputs[0] = is_odd(i / k)? 0x0000000000000000 : 0xFFFFFFFFFFFFFFFF;
		gen_inputs(inputs + (count - 6), count - 1, i);
		return i < (k * 2);
	}
}

void eval_inputs(uint64_t *inputs, uint64_t *outputs, struct cell_t *cells)
{
	const size_t ios = CGP_WIDTH * CGP_HEIGHT;
	uint64_t cache[CGP_INPUTS + ios + CGP_OUTPUTS];

	memcpy(cache, inputs, CGP_INPUTS * sizeof(uint64_t));
}

void expected_outputs(uint64_t *outputs, size_t count)
{
	assert(count > 0);

	switch(count) {
	case 1:
		outputs[0] = 0x00000002;
		break;
	case 2:
		outputs[0] = 0x00000008;
		outputs[1] = 0x0000000E;
		break;
	case 3:
		outputs[0] = 0x00000080;
		outputs[1] = 0x000000E8;
		outputs[2] = 0x000000FE;
		break;
	case 4:
		outputs[0] = 0x00008000;
		outputs[1] = 0x0000E880;
		outputs[2] = 0x0000FEE8;
		outputs[3] = 0x0000FFFE;
		break;
	case 5:
		outputs[0] = 0x80000000;
		outputs[1] = 0xE8808000;
		outputs[2] = 0xFEE8E880;
		outputs[3] = 0xFFFEFEE8;
		outputs[4] = 0xFFFFFFFE;
		break;
	case 6:
		outputs[0] = 0x8000000000000000;
		outputs[1] = 0xE880800080000000;
		outputs[2] = 0xFEE8E880E8808000;
		outputs[3] = 0xFFFEFEE8FEE8E880;
		outputs[4] = 0xFFFFFFFEFFFEFEE8;
		outputs[6] = 0xFFFFFFFFFFFFFFFE;
		break;
	default:
		expected_outputs(outputs, count - 1);
	}
}

int fitness_compute(const struct chromo_t *c, fitness_t *value)
{
	struct cell_t *cells = chromo_alap(c);
	uint64_t inputs[CGP_INPUTS];
	uint64_t outputs[CGP_OUTPUTS];
	size_t incorrect = 0;

	size_t i = 0;
	while(gen_inputs(inputs, CGP_INPUTS, i++)) {
		eval_inputs(inputs, outputs, cells);
		expected_outputs(outputs);
	}

	*value = incorrect;
	return 0;
}

int fitness_isbest(fitness_t f)
{
	return f == 0;
}
