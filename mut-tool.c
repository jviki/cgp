/**
 * mut-tool.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "chromo.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	int ccount = 1;
	if(argc >= 2)
		ccount = atoi(argv[1]);

	if(ccount <= 0) {
		fprintf(stderr, "Chromosome count must be a positive number\n");
		return 1;
	}

	struct chromo_t *c = chromo_alloc(1);

	if(c == NULL) {
		fprintf(stderr, "Chromosome allocation has failed\n");
		return 2;
	}

	int err = 0;

	for(int i = 0; i < ccount; ++i) {
		if(chromo_parse(stdin, c)) {
			fprintf(stderr, "Chromosome number %d couldn't be parsed\n", i);
			err = 1;
		}

		chromo_mut(c);
		chromo_print(stdout, c);
		printf("\n");
	}

	chromo_free(c);
	return err;
}

