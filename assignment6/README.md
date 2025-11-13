# Assignment 6 - OpenMP stencil comparison

- This assignment compares three different OpenMP implementations of a stencil computation.  
- The goal was to run all three versions, measure the execution time, and explain the differences in performance.

The three programs used:

- stencil_opt2.c
- stencil_opt4.c
- stencil_opt6.c

# Results

stencil_opt2:
init = 0.014374
flush = 68.373434
stencil = 56.076041
total = 124.469032

stencil_opt4:
init = 0.020915
flush = 64.111631
stencil = 57.141885
total = 121.282829

stencil_opt6:
init = 0.022857
flush = 64.030528
stencil = 55.863498
total = 122.397180


# Answers to the required questions

- 1. How many threads did your CPU use?

All three programs printed:
Running with 8 thread(s) - so the execution used 8 OpenMP threads.


- 2. What parts of the code were improved? What strategies were used?

The main impprovments between versions are:
- stencil_opt2 (baseline): it uses more #pragma omp parallel for loops, every loop has an implicit barrier so threads keep waiting on each other and becuase of that it has overhead and becomes slowest version.

- stencil_opt4: Has one big parallel region around the whoole iteration loop, flush part uses nowait so removs one unnecessary barrier, less synchronization no constant thread creation

- stencil_opt6: Splits work manually so each thread gets own part of array, this improves memory locality , uses only few explicit barriers where neded, structure more organized but on this system perf. close to opt4


- 3. What is the difference between explicit and implicit barriers inside the code and did they exist inside any of these examples? What do they actually mean? 

# Implicit barriers:
- OpenMP automatically adds them at the end of omp for lops (unless nowait is used).
- When there is an implicit barrier, all threads must wait for each other before moving on.
#In code exmp:
- opt2 has a lot of implicit barriers because every omp for ends with one.
- opt4 has fewer of them, and one is removed using nowait.
- opt6 almost has none because it doesn’t use omp for inside the main loop.

# Explicit barriers:
- These are added manually using #pragma omp barrier.
- They are only usedd when synchronization is really needed.
#In cod exmp:
- opt6 uses explicit barriers after initialization, after the stencil step, and after the pointer swap.

# Conclusion

- opt2 is the slowest because it has the most synchronization and overhead.

- opt4 is the fastest overall since it removes unnecessary barriers and uses one big parallel region.

- opt6 is more advanced and has better memory locality, but the speed on this system ends up close to opt4.