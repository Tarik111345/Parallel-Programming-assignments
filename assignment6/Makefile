CC = gcc
CFLAGS = -fopenmp -Wall -std=c11 -march=native -O2
LDFLAGS = -lm

SOURCES = stencil_opt2.c stencil_opt4.c stencil_opt6.c
EXECUTABLES = $(SOURCES:.c=)
UTILS = timer.o malloc2D.o

all: $(EXECUTABLES)

%: %.c $(UTILS)
	$(CC) $(CFLAGS) $< $(UTILS) -o $@ $(LDFLAGS)

timer.o: timer.c timer.h
	$(CC) $(CFLAGS) -c timer.c -o $@

malloc2D.o: malloc2D.c malloc2D.h
	$(CC) $(CFLAGS) -c malloc2D.c -o $@

clean:
	rm -f *.o stencil_opt2 stencil_opt4 stencil_opt6
