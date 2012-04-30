/**
 * func_swap.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "func.h"
#include "rndgen.h"
#include <stdlib.h>

/**
 * Available functions.
 */
enum func_enum_t {
	F_CMP_SWAP
};

size_t func_inputs_max(void)
{
	return 2;
}

size_t func_outputs_max(void)
{
	return 2;
}

size_t func_inputs(func_t f)
{
	return 2;
}

size_t func_outputs(func_t f)
{
	return 2;
}


const char *func_to_str(func_t f)
{
	switch((enum func_enum_t) f) {
	case F_CMP_SWAP:
		return "C&S";
	default:
		return "<?>";
	}
}

void func_gen(func_t *f)
{
	*f = 0;
}

void func_mut(func_t *f)
{
	func_gen(f);
}

void func_eval64(func_t f, uint64_t *op, uint64_t *dst)
{
	switch((enum func_enum_t) f) {
	case F_CMP_SWAP:
		dst[0] = op[0] & op[1];
		dst[1] = op[0] | op[1];
		break;
	default:
		abort();
	}
}
