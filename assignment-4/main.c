#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sum_algorithms.h"

#define ORDERS_OF_MAGNITUDE 1.0e9

// Print one test result
static void print_result(const char *label,
                         double test_sum,
                         long double accurate_ld,
                         double runtime_sec)
{
    double accurate_d = (double)accurate_ld;
    double diff = test_sum - accurate_d;
    double rel  = diff / accurate_d;
    printf("  accurate %-20.16lg  sum %-20.16lg  diff % .10lg  rel % .10lg  runtime %.6lfs   %s\n",
           accurate_d, test_sum, diff, rel, runtime_sec, label);
}

int main(void)
{
    printf("========================================\n");
    printf(" Global Sum (Leblanc Problem)\n");
    printf("========================================\n\n");

    // Test array sizes from 2^10 to 2^24
    for (int p = 10; p <= 24; ++p) {
        long n = 1L << p;
        long half = n >> 1;

        const double high = 1.0e-1;
        const double low  = 1.0e-1 / ORDERS_OF_MAGNITUDE;

        // Reference accurate value
        long double accurate_ld = (long double)half * (long double)high
                                + (long double)half * (long double)low;

        double *a = (double*)malloc((size_t)n * sizeof(double));
        if (!a) {
            fprintf(stderr, "Allocation failed for n=%ld\n", n);
            return 1;
        }
        for (long i = 0; i < n; ++i) a[i] = (i < half) ? high : low;

        printf("----------------------------------------\n");
        printf(" TEST n = 2^%d = %ld elements\n", p, n);

        struct timespec t0;

        // Long double
        cpu_timer_start(&t0);
        double s_ld = (double)do_sum_longdouble(a, n);
        double t_ld = cpu_timer_stop(t0);
        print_result("Long double", s_ld, accurate_ld, t_ld);

        // Pairwise
        cpu_timer_start(&t0);
        double s_pair = do_sum_pairwise(a, n);
        double t_pair = cpu_timer_stop(t0);
        print_result("Pairwise", s_pair, accurate_ld, t_pair);

        // Kahan
        cpu_timer_start(&t0);
        double s_kahan = do_sum_kahan(a, n);
        double t_kahan = cpu_timer_stop(t0);
        print_result("Kahan", s_kahan, accurate_ld, t_kahan);

        // Knuth
        cpu_timer_start(&t0);
        double s_knuth = do_sum_knuth(a, n);
        double t_knuth = cpu_timer_stop(t0);
        print_result("Knuth", s_knuth, accurate_ld, t_knuth);

        free(a);
        printf("\n");
    }

    printf("========================================\n");
    printf(" Tests complete.\n");
    printf("========================================\n");
    return 0;
}
