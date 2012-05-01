/**
 * cgp.h
 * Author: Jan Viktorin <xvikto03 (at) stud.fit.vutbr.cz>
 */

#ifndef CGP_H
#define CGP_H

#include "chromo.h"
#include "fitness.h"
#include <stdlib.h>

/**
 * CGP state.
 */
struct cgp_t {
	struct chromo_t *c;
	fitness_t *f;
	int found_best;
	size_t gener;
};

/**
 * Initializes CGP state.
 */
int cgp_init(struct cgp_t *cgp);

/**
 * Finalizes CGP state (cleans up resources).
 */
void cgp_fini(struct cgp_t *cgp);

/**
 * Generates a population at random and evaluates it.
 */
int cgp_gen_popul(struct cgp_t *cgp);

/**
 * Generates the initial population based on the given chromosomes.
 * If zero chromosomes given the effect is the same as `cgp_gen_popul`.
 */
int cgp_gen_popul_from(struct cgp_t *cgp, struct chromo_t *c, size_t count);

/**
 * Says true when the CGP is done.
 * The generated population must be evaluated when calling
 * this function.
 */
int cgp_done(const struct cgp_t *cgp);

/**
 * Generates next population.
 */
int cgp_next_popul(struct cgp_t *cgp);

/**
 * Evaluates current population (cgp->gener > 0) by a fitness function.
 */
int cgp_eval_popul(struct cgp_t *cgp);

/**
 * USer defined walking function.
 */
typedef void (*cgp_walk_f)(size_t i, const struct chromo_t *, fitness_t, void *);

/**
 * Walks the current population. User can pass a context information
 * that is passed during the walk.
 */
void cgp_walk_popul(struct cgp_t *cgp, cgp_walk_f walkf, void *ctx);

#endif
