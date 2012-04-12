/**
 * rndgen.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "rndgen.h"

size_t rndgen_next(void)
{
	int r = rand();
	return (size_t) r;
}

size_t rndgen_range(size_t max)
{
	size_t r = rndgen_next();
	return r % (max + 1);
}

