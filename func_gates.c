/**
 * func_gates.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "func.h"

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
enum func_t {
	F_AND,
	F_OR,
	F_XOR
};

const char *func_to_str(enum func_t f)
{
	switch(f) {
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
