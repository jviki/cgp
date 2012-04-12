/**
 * func_gates.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "func.h"

#define FUNC_INPUTS  2
#define FUNC_OUTPUTS 1

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
