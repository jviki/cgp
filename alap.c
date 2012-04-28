/**
 * alap.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "alap.h"
#include "func.h"
#include "chromo_def.h"
#include "cgp_config.h"
#include <stdio.h>
#include <assert.h>

//
// List of cells
//

static
struct cell_t *llist_prepend(struct cell_t *head, struct cell_t *el)
{
	assert(el != NULL);
	el->next = head;
	return el;
}

//
// Array of ports
//

static
size_t ports_count(void)
{
	return CGP_OUTPUTS
		+ func_inputs_max() * (CGP_WIDTH * CGP_HEIGHT);
}

static
size_t ports_add(port_t *ports, size_t count, port_t p)
{
	// this is correct
	// the counts should match
	assert(count < ports_count());

	ports[count++] = p;
	return count;
}

static
size_t ports_from_chromo(port_t *ports, port_t *outputs)
{
	size_t count = 0;

	for(size_t i = 0; i < CGP_OUTPUTS; ++i)
		count = ports_add(ports, count, outputs[i]);

	return count;
}

static
size_t ports_add_inputs(port_t *ports, size_t count, const struct cell_t *c)
{
	for(size_t i = 0; i < func_inputs_max(); ++i) {
		const port_t p = c->inputs[i];

		if(p != NULL_PORT)
			count = ports_add(ports, count, p);
	}

	return count;
}

static
int ports_contain(port_t *ports, size_t count, port_t p)
{
	for(size_t i = 0; i < count; ++i)
		if(p == ports[i])
			return 1;

	return 0;
}

static
int all_outputs_in(port_t *ports, size_t count, const struct cell_t *cell)
{
	size_t first;
	size_t last;

	cell_outputs(cell, &first, &last);

	for(size_t j = first; j <= last; ++j)
		if(!ports_contain(ports, count, (port_t) j))
			return 0;

	return 1;
}

//
// ALAP implementation
//

struct cell_t *chromo_alap(const struct chromo_t *c)
{
	port_t ports[ports_count()];
	size_t ports_count = ports_from_chromo(ports, c->outputs);
	struct cell_t *alap = NULL;

	for(size_t i = CGP_WIDTH * CGP_HEIGHT; i > 0; --i) {
		struct cell_t *curr = c->cell + (i - 1);

		if(all_outputs_in(ports, ports_count, curr))
			alap = llist_prepend(alap, curr);

		ports_count = ports_add_inputs(ports, ports_count, curr);
	}

	return alap;
}
