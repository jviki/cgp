/**
 * func_minmax.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "func.h"
#include "rndgen.h"
#include <stdlib.h>

/**
 * Available functions.
 */
enum func_enum_t {
	F_AND,
	F_OR,
	F_AND3,
	F_OR3,
	F_SWAP
};

size_t func_inputs_max(void)
{
	return 3;
}

size_t func_outputs_max(void)
{
	return 2;
}

size_t func_inputs(func_t f)
{
	switch((enum func_enum_t) f) {
	case F_AND:
	case F_OR:
	case F_SWAP:
		return 2;

	case F_AND3:
	case F_OR3:
		return 3;

	default:
		abort();
	}
}

size_t func_outputs(func_t f)
{
	if(F_SWAP == (enum func_enum_t) f)
		return 2;

	return 1;
}

#define FUNC_COUNT 5

size_t func_count(void)
{
	return FUNC_COUNT;
}

const char *func_to_str(func_t f)
{
	switch((enum func_enum_t) f) {
	case F_AND:
		return "AND";
	case F_OR:
		return "OR";
	case F_OR3:
		return "OR3";
	case F_AND3:
		return "AND3";
	case F_SWAP:
		return "SWAP";
	default:
		return "<?>";
	}
}

void func_gen(func_t *f)
{
	*f = rndgen_range(FUNC_COUNT - 1);
}

void func_mut(func_t *f)
{
	func_gen(f);
}

void func_eval64(func_t f, uint64_t *op, uint64_t *dst)
{
	switch((enum func_enum_t) f) {
	case F_AND:
		*dst = op[0] & op[1];
		break;
	case F_OR:
		*dst = op[0] | op[1];
		break;
	case F_OR3:
		*dst = op[0] | op[1] | op[2];
		break;
	case F_AND3:
		*dst = op[0] & op[1] & op[2];
		break;
	case F_SWAP:
		dst[0] = op[1];
		dst[1] = op[0];
		break;
	default:
		abort();
	}
}
