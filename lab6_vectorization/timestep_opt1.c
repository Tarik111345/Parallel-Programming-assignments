#include <math.h>
#include "timestep.h"
#define REAL_CELL 1

double timestep(int ncells, double g, double sigma, int* restrict celltype,
                double* restrict H, double* restrict U, double* restrict V,
                double* restrict dx, double* restrict dy) {
    double wavespeed, xspeed, yspeed, dt;
    double mymindt = 1.0e20;

    #pragma omp simd reduction(min:mymindt)
    for (int ic = 0; ic < ncells; ic++) {
        if (celltype[ic] == REAL_CELL) {
            wavespeed = sqrt(g * H[ic]);
            xspeed = (fabs(U[ic]) + wavespeed) / dx[ic];
            yspeed = (fabs(V[ic]) + wavespeed) / dy[ic];
            dt = sigma / (xspeed + yspeed);
            if (dt < mymindt) mymindt = dt;
        }
    }
    return mymindt;
}
