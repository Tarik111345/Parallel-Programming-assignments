#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <chrono>

#ifndef V
#define V 4
#endif

struct Particle {
    double x[V];
    double y[V];
    double z[V];
    double mass[V];
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    long N = atol(argv[1]);
    long groups = (N + V - 1) / V;

    std::vector<Particle> aosoa(groups);

    for (long g = 0; g < groups; ++g) {
        for (int i = 0; i < V; ++i) {
            long idx = g * V + i;
            if (idx < N) {
                aosoa[g].x[i] = sin(idx * 0.001);
                aosoa[g].y[i] = cos(idx * 0.001);
                aosoa[g].z[i] = sqrt(idx + 1.0);
                aosoa[g].mass[i] = 1.0 + (idx % 100) * 0.01;
            }
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    double sum = 0.0;
    for (long g = 0; g < groups; ++g) {
        for (int i = 0; i < V; ++i) {
            long idx = g * V + i;
            if (idx >= N) break;
            double v2 = aosoa[g].x[i] * aosoa[g].x[i] +
                        aosoa[g].y[i] * aosoa[g].y[i] +
                        aosoa[g].z[i] * aosoa[g].z[i];
            sum += 0.5 * aosoa[g].mass[i] * v2;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double ns = std::chrono::duration<double, std::nano>(end - start).count();
    double ns_per_elem = ns / static_cast<double>(N);

    printf("%ld,%d,%.3f,%.3f,%e\n", N, V, ns, ns_per_elem, sum);

    return 0;
}
