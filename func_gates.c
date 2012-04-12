/**
 * func_gates.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "func.h"
#include "rndgen.h"

size_t func_inputs_max(void)
{
	return 2;
}

size_t func_outputs_max(void)
{
	return 1;
}

/**
 * Available functions.
 */
enum func_enum_t {
	F_AND,
	F_OR,
	F_XOR
};

#define FUNC_COUNT 3

const char *func_to_str(func_t f)
{
	switch((enum func_enum_t) f) {
	case F_AND:
		return "AND";
	case F_OR:
		return "OR";
	case F_XOR:
		return "XOR";
	default:
		return "<?>";
	}
}

void func_gen(func_t *f)
{
	*f = rndgen_range(FUNC_COUNT - 1);
}

