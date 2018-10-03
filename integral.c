/*
============================================================================
Filename    : integral.c
Author      : Your names goes here
SCIPER		: Your SCIPER numbers
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "function.c"

double integrate (int num_threads, int samples, int a, int b, double (*f)(double));

int main (int argc, const char *argv[]) {

    int num_threads, num_samples, a, b;
    double integral;

    if (argc != 5) {
		printf("Invalid input! Usage: ./integral <num_threads> <num_samples> <a> <b>\n");
		return 1;
	} else {
        num_threads = atoi(argv[1]);
        num_samples = atoi(argv[2]);
        a = atoi(argv[3]);
        b = atoi(argv[4]);
	}

    set_clock();

    /* You can use your self-defined funtions by replacing identity_f. */
    integral = integrate (num_threads, num_samples, a, b, identity_f);

    printf("- Using %d threads: integral on [%d,%d] = %.15g computed in %.4gs.\n", num_threads, a, b, integral, elapsed_time());

    return 0;
}


double integrate (int num_threads, int samples, int a, int b, double (*f)(double)) {
	double integral;
	rand_gen rg;
	double p_integral;
	double random;
	integral=0;
	omp_set_num_threads(num_threads);
	#pragma omp parallel private(random, p_integral, rg)
	{
		p_integral=0;
		rg=init_rand();
		#pragma omp for
		for(int i=0;i<samples;i++){
			random=next_rand(rg);
			random=random*(b-a);
			random+=a;
			p_integral+=f(random)*(b-a);	
		}
		#pragma omp critical
		{
		integral+=p_integral;
		}
	}
	integral=integral/samples;
	free_rand(rg);	
	return integral;
}
