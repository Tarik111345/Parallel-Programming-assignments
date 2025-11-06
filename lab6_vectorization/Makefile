CC=gcc
CFLAGS=-O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd \
 -march=native -mtune=native -mprefer-vector-width=256 \
 -fopt-info-vec-optimized -fopt-info-vec-missed

all: opt1 opt2 opt3

opt1: main.c timer.c timestep_opt1.c
	$(CC) $(CFLAGS) -o opt1 main.c timer.c timestep_opt1.c -lm

opt2: main.c timer.c timestep_opt2.c
	$(CC) $(CFLAGS) -o opt2 main.c timer.c timestep_opt2.c -lm

opt3: main.c timer.c timestep_opt3.c
	$(CC) $(CFLAGS) -fno-trapping-math -fno-math-errno -o opt3 main.c timer.c timestep_opt3.c -lm

clean:
	rm -f opt1 opt2 opt3 *.o
