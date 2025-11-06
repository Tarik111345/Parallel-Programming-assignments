Vectorization 

The goal of this lab was to analyze and improve vectorization of the timestep function from the Example_03 program.  
We created three versions of the function:
- timestep_opt1.c – base optimization  
- timestep_opt2.c –  is thte improved with OpenMP SIMD and reduction directives  
- timestep_opt3.c – is the final optimized version using AVX instructions and additional flags

LIKWID was use to measuere performance with :
sudo likwid-perfctr -C 0 -f -g FLOPS_DP ./optX


Note about WSL2

Since this lab was run under WSL2 (Windows Subsystem for Linux),
some hardware counters such as MHz, MFLOPS, and CPI returned 0.
This happens because WSL2 runs inside Hyper-V virtualization, which does not allow direct access to CPU performance registers (MSRs).


Conclusions

- The code was compiled and executed successfully for all versions.

- Compiler reports confirmed vvectorization with 32-byte AVX instructions.

- The final version (opt3) achieved almost full vectorization (~100%).

- LIKWID partially worked under WSL2, showing correct instruction statistics but mising performance values due to virtualization limits.

- Numerical results stayedf identical across all optimizations, proving correctness.


Tarik Hadrovic 