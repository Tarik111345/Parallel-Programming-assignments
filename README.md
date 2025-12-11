# Lab 10 Report: GPU Portability and Performance

## 1. Local Machine Tests (No GPU)

I tested the code on the lab computer. This computer does not have an NVIDIA GPU, only a CPU.

### OpenMP (Success)
This worked fine. The time was about 0.04 ms. OpenMP is portable because it runs on the CPU when no GPU is available.

### OpenACC (Slow)
This also worked, but it was slow (0.04s). Since there is no GPU, the compiler made it run on the CPU.

### CUDA (Failed)
This failed to run. The error "nvcc not found" happens because I don't have NVIDIA drivers or hardware installed on this PC.

### OpenCL (Failed)
This failed with a runtime error "clGetDeviceIDs". The code compiled, but it crashed because the computer is missing the necessary OpenCL drivers for the hardware.

---

## 2. Server Tests (With GPU)

I connected to the lab server (10.1.8.100) which has a strong NVIDIA GPU.

### OpenACC (Comparison of Kernels)
I ran multiple versions of OpenACC to see the difference in optimization.

Here are the results from the screenshot:
1. **StreamTriad_kern1 (2.22s):** This was very slow. It is slow because it copies data back and forth between CPU and GPU constantly.
2. **StreamTriad_par4 (0.001s):** This was extremely fast. It uses "data regions" to keep data on the GPU, so it doesn't waste time copying.

## Conclusion

* **Portability:** OpenMP and OpenACC are best for portability because they work on the local PC (CPU) even without a GPU.
* **Performance:** CUDA and optimized OpenACC (par4) are the fastest, but they require a real GPU to work.
* **Optimization:** The serdver test showed that managing data (OpenACC par4) is critical. It was 2000x faster than the unoptimized version (kern1).