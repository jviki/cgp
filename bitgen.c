/**
 * bitgen.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "bitgen.h"
#include <string.h>
#include <assert.h>

/**
 * Constants used for any generator.
 */
static const uint64_t init[] = {
	0xAAAAAAAAAAAAAAAA,
	0xCCCCCCCCCCCCCCCC,
	0xF0F0F0F0F0F0F0F0,
	0xFF00FF00FF00FF00,
	0xFFFF0000FFFF0000,
	0xFFFFFFFF00000000
};

static const uint64_t sorted[] = {
	0xFFFFFFFFFFFFFFFE,
	0xFFFFFFFEFFFEFEE8,
	0xFFFEFEE8FEE8E880,
	0xFEE8E880E8808000,
	0xE880800080000000,
	0x8000000000000000,
};

static const size_t init_len = sizeof(init) / sizeof(uint64_t);

int bitgen_init(struct bitgen_t *g, size_t width)
{

	if(width == 0)
		return 1;

	void *m = malloc(width * sizeof(uint64_t));
	if(m == NULL)
		return -1;

	g->last = (uint64_t *) m;
	
	for(size_t i = 0; i < width && i < init_len; ++i)
		g->last[i] = init[i];
	for(size_t i = init_len; i < width; ++i)
		g->last[i] = 0;

	g->width = width;
	g->valid = 1;
	return 0;
}

void bitgen_fini(struct bitgen_t *g)
{
	assert(g->width > 0);

	free(g->last);
	g->last  = NULL;
	g->width = 0;
	g->valid = 0;
}

int bitgen_next(struct bitgen_t *g, uint64_t *d)
{
	assert(g->width > 0);

	if(!g->valid)
		return 0;

	memcpy(d, g->last, sizeof(uint64_t) * g->width);

	if(g->width <= 6) {
		g->valid = 0;
		return 1;
	}

	int flip = 1;

	for(size_t i = init_len; i < g->width; ++i) {
		if(!flip)
			break;

		if(flip && g->last[i] == 0) {
			flip = 0;
			g->last[i] = 0xFFFFFFFFFFFFFFFF;
		}
		else if(flip && g->last[i] == 0xFFFFFFFFFFFFFFFF) {
			flip = 1;
			g->last[i] = 0;
		}
	}

	if(flip) // carry, going to overflow thus finish
		g->valid = 0;

	return 1;
}

void bitgen_sort(const uint64_t *d, uint64_t *s, size_t width)
{
	assert(width > 0);
	size_t count = 0;

	for(size_t i = 0; i < width; ++i) {
		if(d[i] == 0xFFFFFFFFFFFFFFFF) {
			s[count] = d[i];
			count += 1;
			continue;
		}

		for(size_t j = 0; j < init_len; ++j) {
			if(init[j] == d[i]) {
				s[count] = sorted[j];
				count += 1;
			}
		}
	}

	for(size_t i = 0; i < (width - count); ++i)
		s[count + i] = 0;
}
