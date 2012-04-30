/**
 * main.c
 * Copyright (C) 2012 Jan Viktorin
 */

#include "cgp.h"
#include "cgp_config.h"
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>

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

	if(fitness_isbest(f)) {
		printf("Success: ");
		printf(FITNESS_FMT "\t", f);
		chromo_print(stdout, c);
		fputc('\n', stdout);
	}
	else if(!cgp->found_best) {
		printf(FITNESS_FMT ": ", f);
		chromo_print(stdout, c);
		fputc('\n', stdout);
	}
}

int cgp_run(size_t *gener, fitness_t *best_fitness)
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

		if(cnt % 100 == 0)
			printf("\rAvarage fitness: %lf", ((double) tot) / cnt);
		//////////////
	}

	*gener = cgp.gener;
	printf("\nGenerations: %zu\n", cgp.gener);

	cgp_walk_popul(&cgp, &find_best_fitness, best_fitness);
	printf("Best: %zu\n", *best_fitness);

	cgp_walk_popul(&cgp, &print_chromo, &cgp);
	cgp_fini(&cgp);
	return 0;

error_fini:
	cgp_fini(&cgp);
	return 1;
}

int main(int argc, char **argv)
{
	int count = 1;
	if(argc >= 2)
		count = atoi(argv[1]);

	if(count < 1) {
		fprintf(stderr, "Invalid count of CGP evaluations, must be positive: %d\n", count);
		return -1;
	}

	size_t gener = 0;
	size_t runs  = 0;

	for(int i = 0; i < count; ++i) {
		struct timeval now;
		gettimeofday(&now, NULL);

		srand(now.tv_usec);

		fitness_t f;
		size_t g;
		cgp_run(&g, &f);

		if(fitness_isbest(f)) {
			gener += g;
			runs  += 1;
		}
	}

	printf("Avarage generations: %zu\n", gener / runs);
}
