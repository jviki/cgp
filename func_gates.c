/**
 * func_gates.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "func.h"
#include "rndgen.h"
#include <stdlib.h>

size_t func_inputs_max(void)
{
	return 2;
}

size_t func_outputs_max(void)
{
	return 1;
}

size_t func_inputs(func_t f)
{
	return 2;
}

size_t func_outputs(func_t f)
{
	return 1;
}

/**
 * Available functions.
 */
enum func_enum_t {
	F_AND,
	F_OR,
	F_XOR,
	F_NOR,
	F_NAND,
	F_NXOR
};

#define FUNC_COUNT 6

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
	case F_XOR:
		return "XOR";
	case F_NOR:
		return "NOR";
	case F_NAND:
		return "NAND";
	case F_NXOR:
		return "NXOR";
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
	case F_XOR:
		*dst = op[0] ^ op[1];
		break;
	case F_NOR:
		*dst = ~(op[0] | op[1]);
		break;
	case F_NAND:
		*dst = ~(op[0] & op[1]);
		break;
	case F_NXOR:
		*dst = ~(op[0] ^ op[1]);
		break;
	default:
		abort();
	}
}
