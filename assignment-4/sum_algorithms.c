#define _POSIX_C_SOURCE 199309L
#include <math.h>
#include <time.h>
#include "sum_algorithms.h"

// Start timer
void cpu_timer_start(struct timespec *tstart_cpu) {
    clock_gettime(CLOCK_MONOTONIC, tstart_cpu);
}

// Stop timer and return elapsed seconds
double cpu_timer_stop(struct timespec tstart_cpu) {
    struct timespec tstop_cpu, tresult;
    clock_gettime(CLOCK_MONOTONIC, &tstop_cpu);
    tresult.tv_sec  = tstop_cpu.tv_sec  - tstart_cpu.tv_sec;
    tresult.tv_nsec = tstop_cpu.tv_nsec - tstart_cpu.tv_nsec;
    return (double)tresult.tv_sec + (double)tresult.tv_nsec * 1.0e-9;
}

// Regular double precision sum
double do_sum(const double *restrict a, long n) {
    double s = 0.0;
    for (long i = 0; i < n; ++i) s += a[i];
    return s;
}

// Long double version for higher precision reference
long double do_sum_longdouble(const double *restrict a, long n) {
    long double s = 0.0L;
    for (long i = 0; i < n; ++i) s += (long double)a[i];
    return s;
}

// Pairwise recursive summation
static double pairwise_rec(const double *restrict a, long n) {
    if (n <= 2) return n == 2 ? a[0] + a[1] : (n == 1 ? a[0] : 0.0);
    long mid = n >> 1;
    return pairwise_rec(a, mid) + pairwise_rec(a + mid, n - mid);
}
double do_sum_pairwise(const double *restrict a, long n) {
    return pairwise_rec(a, n);
}

// Kahan summation – compensates floating-point error
double do_sum_kahan(const double *restrict a, long n) {
    double sum = 0.0, c = 0.0;
    for (long i = 0; i < n; ++i) {
        double y = a[i] - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

// Knuth summation – improved version of Kahan
double do_sum_knuth(const double *restrict a, long n) {
    double sum = 0.0, c = 0.0;
    for (long i = 0; i < n; ++i) {
        double t = sum + a[i];
        if (fabs(sum) >= fabs(a[i]))
            c += (sum - t) + a[i];
        else
            c += (a[i] - t) + sum;
        sum = t;
    }
    return sum + c;
}
