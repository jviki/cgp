/**
 * fitness-tool.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "chromo.h"
#include "fitness.h"

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
	int err = 0;

	for(int i = 0; i < ccount; ++i) {
		if(chromo_parse(stdin, chromo_at(c, (size_t) i))) {
			fprintf(stderr, "Chromosome number %d couldn't be parsed\n", i);
			err = 1;
		}
	}

	if(err) {
		chromo_free(c);
		return 2;
	}

	for(int i = 0; i < ccount; ++i) {
		fitness_t value;

		if(fitness_compute(chromo_at(c, (size_t) i), &value)) {
			fprintf(stderr, "Failed to compute fitness for chromosome %d\n", i);
			err = 1;
		}
		else {
			printf(FITNESS_FMT "\n", value);
		}
	}

	chromo_free(c);
	return err? 3 : 0;
}
