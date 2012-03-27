/**
 * cgp.h
 * Author: Jan Viktorin <xvikto03 (at) stud.fit.vutbr.cz>
 */

#ifndef CGP_H
#define CGP_H

#include <stdlib.h>

/**
 * Configuration of the CGP.
 * Consists of:
 *  w       ... number of elements (width)
 *  h       ... number of elements (height)
 *  l       ... L back parameter
 *  gen_cnt ... count of generations
 */
struct cgp_t {
	size_t w;
	size_t h;
	size_t l;
	size_t gen_cnt;
};

#endif
