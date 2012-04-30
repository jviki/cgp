/**
 * chromo-tool.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "chromo.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
	int ccount = 1;
	if(argc >= 2)
		ccount = atoi(argv[1]);

	if(ccount <= 0) {
		fprintf(stderr, "Chromosome count must be a positive number\n");
		return 1;
	}

	struct chromo_t *c = chromo_alloc((size_t) ccount);

	if(c == NULL) {
		fprintf(stderr, "Chromosome allocation has failed\n");
		return 2;
	}

	srand(time(NULL));
	for(int i = 0; i < ccount; ++i) {
		struct chromo_t *current = chromo_at(c, (size_t) i);
		chromo_gen(current);
		chromo_print(stdout, current);
		printf("\n");
	}

	chromo_free(c);
	return 0;
}

