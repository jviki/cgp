/**
 * main.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "cgp.h"
#include "cgp_config.h"
#include <errno.h>
#include <stdio.h>
#include <time.h>

void handle_error(const char *msg)
{
	if(errno != 0)
		perror(msg);
	else
		fprintf(stderr, "Error: %s\n", msg);
}

void find_best_fitness(size_t i, const struct chromo_t *c, fitness_t f, void *ctx)
{
	fitness_t *bestf = (fitness_t *) ctx;

	if(i == 0)
		*bestf = f;
	else if(fitness_cmp(f, *bestf) > 0)
		*bestf = f;
}

void print_chromo(size_t i, const struct chromo_t *c, fitness_t f, void *ctx)
{
	struct cgp_t *cgp = (struct cgp_t *) ctx;

	if(cgp->found_best && fitness_isbest(f)) {
		printf(FITNESS_FMT "\t", f);
		chromo_print(stdout, c);
		fputc('\n', stdout);
	}
	else {
		printf(FITNESS_FMT ": ", f);
		chromo_print(stdout, c);
		fputc('\n', stdout);
	}
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	struct cgp_t cgp;

	if(cgp_init(&cgp)) {
		handle_error("cgp_init");
		goto error_fini;
	}
	
	if(cgp_gen_popul(&cgp)) {
		handle_error("gcp_gen_popul");
		goto error_fini;
	}

	//////////////
	fitness_t tot = 0;
	size_t cnt = 0;
	//////////////

	while(!cgp_done(&cgp)) {
		if(cgp_next_popul(&cgp)) {
			handle_error("cgp_next_popul");
			goto error_fini;
		}

		if(cgp_eval_popul(&cgp)) {
			handle_error("cgp_eval_popul");
			goto error_fini;
		}

		//////////////
		fitness_t f;
		cgp_walk_popul(&cgp, &find_best_fitness, &f);
		tot += f;
		cnt += 1;

		if(cnt % 250 == 0)
			printf("\rAvarage fitness: %lf", ((double) tot) / cnt);
		//////////////
	}

	printf("Generations: %zu\n", cgp.gener);
	cgp_walk_popul(&cgp, &print_chromo, &cgp);
	cgp_fini(&cgp);
	return 0;

error_fini:
	cgp_fini(&cgp);
	return 1;
}
