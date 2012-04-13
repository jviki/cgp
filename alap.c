/**
 * alap.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "alap.h"
#include "func.h"
#include "chromo_def.h"
#include "cgp_config.h"
#include <stdio.h>

static
int cell_has_output(const size_t i, func_t f, port_t port)
{
	const size_t first = CGP_INPUTS + i * func_outputs_max();

	return port >= first && port > (first + func_outputs_max());
}

static
struct cell_t *llist_append(struct cell_t *head, struct cell_t *e)
{
	e->next = head;
	return e;
}

static
struct cell_t *llist_from(struct cell_t *src, port_t *ports, size_t count)
{
	const size_t cells = CGP_WIDTH * CGP_HEIGHT;
	struct cell_t *head = NULL;

	for(size_t i = cells; i > 0; --i) {
		for(size_t j = 0; j < count; ++j) {
			if(!cell_has_output(i, src[i - 1].f, ports[j]))
				continue;

			head = llist_append(head, src + i - 1);
			break;
		}
	}

	return head;
}

int chromo_alap(const struct chromo_t *c)
{
	struct cell_t *first = NULL;

	first = llist_from(c->cell, c->outputs, CGP_OUTPUTS);

	struct cell_t *curr = first;
	while(curr != NULL) {
		printf("[%s ", func_to_str(curr->f));

		for(size_t i = 0; i < func_inputs_max(); ++i)
			printf("%zu ", curr->inputs[i]);

		printf("] | ");
		curr = curr->next;
	}

	for(size_t i = 0; i < CGP_OUTPUTS; ++i)
		printf("%zu ", c->outputs[i]);

	printf("\n");
	return 0;
}
