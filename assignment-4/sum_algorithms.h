#ifndef SUM_ALGORITHMS_H
#define SUM_ALGORITHMS_H

#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stddef.h>

// Timing functions
void cpu_timer_start(struct timespec *tstart_cpu);
double cpu_timer_stop(struct timespec tstart_cpu);

// Summation algorithms
double do_sum(const double *restrict a, long n); 
long double do_sum_longdouble(const double *restrict a, long n); 
double do_sum_pairwise(const double *restrict a, long n); 
double do_sum_kahan(const double *restrict a, long n);   
double do_sum_knuth(const double *restrict a, long n);  

#endif
