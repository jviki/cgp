/**
 * alap.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "alap.h"
#include "func.h"
#include "chromo_def.h"
#include "cgp_config.h"
#include "ports_set.h"
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
void ports_from_chromo(struct ports_set_t *ports, port_t *outputs)
{
	for(size_t i = 0; i < CGP_OUTPUTS; ++i)
		ports_set_put(ports, outputs[i]);
}

static
void ports_add_inputs(struct ports_set_t *ports, const struct cell_t *c)
{
	for(size_t i = 0; i < func_inputs_max(); ++i) {
		const port_t p = c->inputs[i];

		if(p != NULL_PORT)
			ports_set_put(ports, p);
	}
}

static
int outputs_not_in(const struct ports_set_t *set, const struct cell_t *cell)
{
	size_t first;
	size_t last;

	cell_outputs(cell, &first, &last);

	for(size_t j = first; j <= last; ++j) {
		const port_t p = (port_t) j;

		if(ports_set_contain(set, p))
			return 0;
	}

	return 1;
}

//
// ALAP implementation
//

struct cell_t *chromo_alap(const struct chromo_t *c)
{
	struct ports_set_t used_ports;
	if(ports_set_init(&used_ports, ports_count()))
		return NULL;

	ports_from_chromo(&used_ports, c->outputs);
	struct cell_t *alap = NULL;

	for(size_t i = CGP_WIDTH * CGP_HEIGHT; i > 0; --i) {
		struct cell_t *curr = c->cell + (i - 1);

		if(!outputs_not_in(&used_ports, curr)) {
			alap = llist_prepend(alap, curr);
			ports_add_inputs(&used_ports, curr);
		}
	}

	ports_set_fini(&used_ports);
	return alap;
}
