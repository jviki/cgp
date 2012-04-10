/**
 * main.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "cgp.h"
#include <errno.h>
#include <stdio.h>

void handle_error(const char *msg)
{
	if(errno != 0)
		perror(msg);
	else
		fprintf(stderr, "Error: %s\n", msg);
}

void print_chromo(const struct chromo_t *c, fitness_t f, void *ctx)
{
	if(fitness_isbest(f)) {
		printf(FITNESS_FMT "\t", f);
		chromo_print(stdout, c);
		puts("\n");
	}
}

int main(int argc, char **argv)
{
	struct cgp_t cgp;

	if(cgp_init(&cgp)) {
		handle_error("cgp_init");
		goto error_fini;
	}
	
	if(cgp_gen_popul(&cgp)) {
		handle_error("gcp_gen_popul");
		goto error_fini;
	}

	while(!cgp_done(&cgp)) {
		if(cgp_next_popul(&cgp)) {
			handle_error("cgp_next_popul");
			goto error_fini;
		}

		if(cgp_eval_popul(&cgp)) {
			handle_error("cgp_eval_popul");
			goto error_fini;
		}
	}

	cgp_walk_popul(&cgp, &print_chromo, NULL);
	cgp_fini(&cgp);
	return 0;

error_fini:
	cgp_fini(&cgp);
	return 1;
}
