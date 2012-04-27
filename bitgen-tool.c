/**
 * bitgen-tool.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "bitgen.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	if(argc <= 1) {
		fprintf(stderr, "Missing 1 argument: data width\n");
		return 1;
	}

	int width = atoi(argv[1]);

	if(width == 0) {
		fprintf(stderr, "Invalid data width, but be a positive number\n");
		return 2;
	}

	struct bitgen_t g;
	if(bitgen_init(&g, (size_t) width)) {
		fprintf(stderr, "Failed to init the bitgen instance\n");
		return 3;
	}

	uint64_t d[width];
	uint64_t s[width];

	while(bitgen_next(&g, d)) {
		bitgen_sort(d, s, (size_t) width);

		for(int i = 0; i < width; ++i)
			printf("0x%016" PRIx64 " -> 0x%016" PRIx64 "\n", d[i], s[i]);
	}

	bitgen_fini(&g);
	return 0;
}
