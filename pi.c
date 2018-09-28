/*
============================================================================
Filename    : pi.c
Author      : Your names goes here
SCIPER		: Your SCIPER numbers
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

double calculate_pi (int num_threads, int samples);

int main (int argc, const char *argv[]) {

	int num_threads, num_samples;
	double pi;

	if (argc != 3) {
		printf("Invalid input! Usage: ./pi <num_threads> <num_samples> \n");
		return 1;
	} else {
		num_threads = atoi(argv[1]);
		num_samples = atoi(argv[2]);
	}

	set_clock();
	pi = calculate_pi (num_threads, num_samples);

	printf("- Using %d threads: pi = %.15g computed in %.4gs.\n", num_threads, pi, elapsed_time());

	return 0;
}


double calculate_pi (int num_threads, int samples) {
	int tot_inside;
	double x, y;
	int inside,tid,sample;
	rand_gen gen;

	omp_set_num_threads(num_threads);
	printf("Monte carlo pi, %d samples \n", samples);

	#pragma omp parallel private(x, y, inside, tid, gen, sample) shared(tot_inside)
	{
		inside = 0;
		tid = omp_get_thread_num();
		gen = init_rand(tid);

		#pragma omp for
		for (sample=0;sample<samples; sample++) {
			x = next_rand(gen);
			y = next_rand(gen);
			if (x*x+y*y < 1) {
				inside++;
			}
		}

		free_rand(gen);
		#pragma omp critical
			tot_inside += inside;
	}
	double pi = (tot_inside/(double)samples) *4;
	return pi;
}
