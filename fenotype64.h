/**
 * fenotype64.c
 * Copyright (C) 2012 Jan Viktorin
 */

#ifndef FENOTYPE64_H
#define FENOTYPE64_H

#include "chromo_def.h"
#include "cgp_config.h"

void eval_fenotype(const struct cell_t *cells, const port_t *outports,
		const uint64_t *inputs, uint64_t *outputs);

#endif
