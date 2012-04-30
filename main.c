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
	FILE *cfd = (FILE *) ctx;

	if(fitness_isacceptable(f)) {
		printf("Success: " FITNESS_FMT "\n", f);
		chromo_print(cfd, c);
		fputc('\n', cfd);
	}
}

struct run_stats_t {
	size_t gener;
	fitness_t sumf;
	int has_acceptable;
	struct timeval start;
	size_t start_gener;
};

void time_start(struct timeval *t)
{
	gettimeofday(t, NULL);
}

long ms_elapsed(const struct timeval *start)
{
	struct timeval end;
	gettimeofday(&end, NULL);

	long r  = (end.tv_sec - start->tv_sec) * 1000;
	r += (end.tv_usec - start->tv_usec) / 1000;

	return r;
}

void run_stats_update(struct cgp_t *cgp, struct run_stats_t *stats)
{
	fitness_t f;
	cgp_walk_popul(cgp, &find_best_fitness, &f);

	stats->gener += 1;
	stats->sumf  += f;

	if(!stats->has_acceptable) {
		if(fitness_isacceptable(f)) {
			stats->has_acceptable = 1;
			fprintf(stderr, "\nHas acceptable result, now optimizing...\n");
		}
	}

	if(stats->start_gener == 0) {
		time_start(&stats->start);
		stats->start_gener = stats->gener;
	}
	else if(ms_elapsed(&stats->start) > 250) {
		long speed = 4 * (stats->gener - stats->start_gener);
		time_start(&stats->start);
		stats->start_gener = stats->gener;

		fprintf(stderr, "\rAvarage fitness (%6.zu, %6.ld/s): %lf",
				stats->gener, speed, ((double) stats->sumf) / stats->gener);
	}
}

int cgp_run(size_t *gener, fitness_t *best_fitness, FILE *cfd)
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

	struct run_stats_t stats = {
		.gener = 0,
		.sumf  = 0,
		.has_acceptable = 0,
		.start_gener = 0
	};

	while(!cgp_done(&cgp)) {
		if(cgp_next_popul(&cgp)) {
			handle_error("cgp_next_popul");
			goto error_fini;
		}

		if(cgp_eval_popul(&cgp)) {
			handle_error("cgp_eval_popul");
			goto error_fini;
		}

		run_stats_update(&cgp, &stats);
	}

	*gener = cgp.gener;
	printf("\nGenerations: %zu\n", cgp.gener);

	cgp_walk_popul(&cgp, &find_best_fitness, best_fitness);
	printf("Best: %zu\n", *best_fitness);

	cgp_walk_popul(&cgp, &print_chromo, cfd);
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

	char *cfile = "success.chr";
	if(argc >= 3)
		cfile = argv[2];

	FILE *cfd = fopen(cfile, "w");
	if(cfd == NULL) {
		fprintf(stderr, "Invalid file to save best chromosomes: '%s'\n", cfile);
		return -2;
	}
	else {
		fprintf(stderr, "Saving chromosome to file: '%s'\n", cfile);
	}

	size_t gener = 0;
	size_t runs  = 0;

	for(int i = 0; i < count; ++i) {
		struct timeval now;
		gettimeofday(&now, NULL);

		srand(now.tv_usec);

		fitness_t f;
		size_t g;
		cgp_run(&g, &f, cfd);
		fflush(cfd);

		fprintf(stderr, "Elapsed: %ld s\n", ms_elapsed(&now) / 1000);

		if(fitness_isacceptable(f)) {
			gener += g;
			runs  += 1;
		}
	}

	fclose(cfd);
	printf("Avarage generations: %zu\n", gener / runs);
}
