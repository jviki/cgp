/**
 * eval-tool.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "chromo.h"
#include "fenotype64.h"
#include "fitness.h"
#include "alap.h"
#include "bitgen.h"
#include "cgp_config.h"
#include "chromo_def.h"

int read_inputs(uint64_t *inputs, size_t count)
{
	for(size_t i = 0; i < count; ++i) {
		if(scanf(" 0x%" SCNx64, inputs + i) != 1) {
			if(i == 0)
				return 1;

			fprintf(stderr, "Can not read input no. %zu\n", i + 1);
			return -1;
		}
	}

	return 0;
}

int evaluation(struct chromo_t *c)
{
	struct cell_t *cells = chromo_alap(c);
	uint64_t inputs[CGP_INPUTS];
	uint64_t outputs[CGP_OUTPUTS];

	uint64_t mask = CGP_OUTPUTS >= 6? 0xFFFFFFFFFFFFFFFF
			  : (((uint64_t) 1) << (1 << CGP_OUTPUTS)) - 1;

	while(!feof(stdin)) {
		int err = read_inputs(inputs, CGP_INPUTS);
		if(err < 0)
			return 1;
		if(err > 0)
			return 0;

		eval_fenotype(cells, c->outputs, inputs, outputs);

		for(size_t i = 0; i < CGP_OUTPUTS; ++i)
			printf("0x%016" PRIx64 " -> 0x%016" PRIx64 " 0x%016" PRIx64 "\n",
					inputs[i], outputs[i], outputs[i] & mask);
	}

	return 0;
}

int main(int argc, char **argv)
{
	FILE *fd = NULL;
	if(argc >= 2)
		fd = fopen(argv[1], "r");

	if(fd == NULL) {
		fprintf(stderr, "Can not open file with chromosomes\n");
		return 1;
	}

	struct chromo_t *c = chromo_alloc(1);
	int err;

	if((err = chromo_parse(fd, c))) {
		fprintf(stderr, "The chromosome couldn't be parsed: %d\n", err);
		chromo_free(c);
		return 2;
	}

	fclose(fd);

	if(evaluation(c)) {
		chromo_free(c);
		fprintf(stderr, "Error during chromosome evaluation\n");
		return 3;
	}

	chromo_free(c);
	return 0;
}
