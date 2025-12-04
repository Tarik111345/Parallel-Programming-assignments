# Lab 9 Report: BabelSTREAM

# 1. What I did
I ran the BabelSTREAM benchmark to testt memory speed (bandwidth) on three different setups: my CPU, my Integrated Graphics (via WSL), and the Discrete GPU on the lab server.

# 2. Results

## CPU Benchmark (OpenMP)
I ran this on my laptop (WSL).
Command: `./omp-stream -s 1000000`
Note: I had to compile this manually using `g++ -O3 -fopenmp -DOMP ...` because the default makefile was missing the flags and causing Segmentation Faults.
Result (Triad): 19,258.1 MB/s
Integrated GPU (OpenCL)
Since I am using WSL, it couldn't access my Intel graphics card directly.
Workaround: I installed `pocl-opencl-icd` driver. This let me run the OpenCL code on the CPU just to make sure the code works.
Result (Triad): 13,476.1 MB/s
Observation: It is slower than OpenMP because it is emulating GPU behavior on the CPU.

Discrete GPU (CUDA)
I connected to the lab server (`10.1.8.100`) to run this on the NVIDIA GPU.
Config found in logs: 88 blocks * 1024 threads per block.
Result (Triad): 164,693.4 MB/s

# 3. Conclusion

## Why is the Server (CUDA) so fast?
The GPU on the server is vasty faster than my laptop (over 8x faster).
1. Better Memory: It use GDDR6 memory which has huge bandwidth compared to my standard system RAM.
2. More Threads: The GPU runs massive amount of threads at once. In my test, it used:
   `Total Threads = 88 blocks * 1024 threads = 90,112 threads.`

## CPU vs iGPU
My OpenMP result (~19 GB/s) was better than OpenCL (~13 GB/s). This is expected because the OpenCL was actually running on the CPU (via POCL driver) which adds extra overhead compared to the native OpenMP code.