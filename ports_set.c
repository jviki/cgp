/**
 * ports_set.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "ports_set.h"
#include <stdlib.h>
#include <assert.h>

int ports_set_init(struct ports_set_t *set, size_t maxcount)
{
	void *m = calloc(maxcount, sizeof(port_t));
	if(m == NULL)
		return 1;

	set->set = (port_t *) m;
	set->cap = maxcount;
	set->count = 0;
	return 0;
}

void ports_set_fini(struct ports_set_t *set)
{
	assert(set->count > 0);
	assert(set->set != NULL);

	free(set->set);
	set->set = NULL;
	set->count = 0;
}

void ports_set_put(struct ports_set_t *set, port_t p)
{
	assert(set->count < set->cap);

	set->set[set->count++] = p;
}

int ports_set_contain(const struct ports_set_t *set, port_t p)
{
	for(size_t i = 0; i < set->count; ++i)
		if(set->set[i] == p)
			return 1;

	return 0;
}
