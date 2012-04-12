/**
 * cgp.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "cgp.h"
#include "cgp_config.h"
#include <assert.h>

int cgp_init(struct cgp_t *cgp)
{
	cgp->gener = 0;
	cgp->c = chromo_alloc(CGP_POPUL);

	if(cgp->c == NULL)
		return 1;

	cgp->f = malloc(CGP_POPUL * sizeof(fitness_t));
	if(cgp->f == NULL) {
		chromo_free(cgp->c);
		cgp->c = NULL;
		return 2;
	}

	return 0;
}

void cgp_fini(struct cgp_t *cgp)
{
	if(cgp->c != NULL) {
		chromo_free(cgp->c);
		cgp->c = NULL;
	}

	if(cgp->f != NULL) {
		free(cgp->f);
		cgp->f = NULL;
	}
}

int cgp_gen_popul(struct cgp_t *cgp)
{
	for(size_t i = 0; i < CGP_POPUL; ++i)
		chromo_gen(chromo_at(cgp->c, i));

	return 0;
}

int cgp_done(const struct cgp_t *cgp)
{
	return cgp->gener >= CGP_GENER;
}

int cgp_next_popul(struct cgp_t *cgp)
{
	cgp->gener += 1;
	return 0;
}

int cgp_eval_popul(struct cgp_t *cgp)
{
	for(size_t i = 0; i < CGP_POPUL; ++i) {
		if(fitness_compute(chromo_at(cgp->c, i), cgp->f + i))
			return 1;
	}

	return 0;
}

void cgp_walk_popul(struct cgp_t *cgp, cgp_walk_f walkf, void *ctx)
{
	for(size_t i = 0; i < CGP_POPUL; ++i)
		walkf(chromo_at(cgp->c, i), cgp->f[i], ctx);
}
