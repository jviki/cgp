/**
 * cgp.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "cgp.h"
#include "cgp_config.h"
#include <assert.h>
#include <string.h>

int cgp_init(struct cgp_t *cgp)
{
	cgp->gener = 0;
	cgp->found_best = 0;
	cgp->c = chromo_alloc(CGP_POPUL);

	if(cgp->c == NULL)
		return 1;

	cgp->f = malloc(CGP_POPUL * sizeof(fitness_t));
	if(cgp->f == NULL) {
		chromo_free(cgp->c);
		cgp->c = NULL;
		return 2;
	}

	memset(cgp->f, 0, sizeof(fitness_t) * CGP_POPUL);

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

int cgp_done(const struct cgp_t *cgp)
{
	return cgp->gener >= CGP_GENER || cgp->found_best;
}

static
int priv_eval_popul(struct chromo_t *c, size_t len, fitness_t *f, int *found_best)
{
	*found_best = 0;

	for(size_t i = 0; i < CGP_POPUL; ++i) {
		if(fitness_compute(chromo_at(c, i), f + i))
			return 1;

		if(fitness_isbest(f[i]))
			*found_best = 1;
	}

	return 0;
}

int cgp_gen_popul(struct cgp_t *cgp)
{
	for(size_t i = 0; i < CGP_POPUL; ++i)
		chromo_gen(chromo_at(cgp->c, i));

	return priv_eval_popul(cgp->c, CGP_POPUL, cgp->f, &cgp->found_best);
}

int cgp_eval_popul(struct cgp_t *cgp)
{
	assert(cgp->gener > 0);
	return priv_eval_popul(
			chromo_at(cgp->c, 1), CGP_POPUL - 1, cgp->f + 1, &cgp->found_best);
}

static
size_t choose_winner(struct cgp_t *cgp)
{
	size_t winner_i = 0;

	for(size_t i = 0; i < CGP_POPUL; ++i) {
		if(fitness_cmp(cgp->f[i], cgp->f[winner_i]) >= 0)
			winner_i = i;
	}

	return winner_i;
}

int cgp_next_popul(struct cgp_t *cgp)
{
	const size_t winner_i = choose_winner(cgp);
	const struct chromo_t *winner = chromo_at(cgp->c, winner_i);

	chromo_copy(cgp->c, winner);
	cgp->f[0] = cgp->f[winner_i];

	for(size_t i = 1; i < CGP_POPUL - 1; ++i) {
		chromo_copy(chromo_at(cgp->c, i), cgp->c);
		chromo_mut(chromo_at(cgp->c,  i));
	}

	cgp->gener += 1;
	return 0;
}

void cgp_walk_popul(struct cgp_t *cgp, cgp_walk_f walkf, void *ctx)
{
	for(size_t i = 0; i < CGP_POPUL; ++i)
		walkf(chromo_at(cgp->c, i), cgp->f[i], ctx);
}
