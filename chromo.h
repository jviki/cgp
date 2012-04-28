/**
 * chromo.h
 * Author: Jan Viktorin <xvikto03 (at) stud.fit.vutbr.cz>
 */

#ifndef CHROMO_H
#define CHROMO_H

#include <stdlib.h>
#include <stdio.h>

/**
 * Chromosome abstraction.
 */
struct chromo_t;

/**
 * Allocation of a new chromosome.
 * Can allocate an array of chromosomes.
 */
struct chromo_t *chromo_alloc(size_t count);

/**
 * Free of a chromosome dynamically allocated.
 */
void chromo_free(struct chromo_t *c);

/**
 * Creates deep copy of the `src` chromosome. The `dst`
 * chromosome must be allocated. This functions just copies
 * the contents, it doesn't allocate memory.
 * It doesn't copy anything when the pointers have the same
 * target location.
 */
void chromo_copy(struct chromo_t *dst, const struct chromo_t *src);

/**
 * Returns i-th chromosome in the array.
 */
struct chromo_t *chromo_at(struct chromo_t *array, size_t i);

/**
 * Generates a random chromosome.
 */
void chromo_gen(struct chromo_t *c);

/**
 * Mutates the given chromosome.
 */
void chromo_mut(struct chromo_t *c);

/**
 * Prints the chromosome to the given stream.
 */
void chromo_print(FILE *fout, const struct chromo_t *c);

/**
 * Parses a chromosome from the given stream.
 * It returns zero when successful.
 */
int chromo_parse(FILE *fin, struct chromo_t *c);

#endif
