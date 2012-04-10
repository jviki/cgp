/**
 * cgp.h
 * Author: Jan Viktorin <xvikto03 (at) stud.fit.vutbr.cz>
 */

#ifndef CGP_H
#define CGP_H

#include "chromo.h"
#include <stdlib.h>

/**
 * CGP state.
 */
struct cgp_t {
	struct chromo_t *c;
};

/**
 * Generates a population at random.
 */
int cgp_gen_popul(struct cgp_t *cgp);

/**
 * Generates next population.
 */
int cgp_next_popul(struct cgp_t *cgp);

#endif
