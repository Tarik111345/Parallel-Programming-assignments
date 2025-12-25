# Parallel File I/O Assignment

## Setup

I testedd everything on WSL2 with 4 MPI processes.

First I generated the test data:
```bash
gcc file_generator.c -o file_generator -lm
./file_generator
```
Got a CSV file with 15 million records (~880 MB).

Then ran each example:
```bash
cd Example_01
make clean && make && make run
```

---

## Results

Here's what i got:

**Example_01:** 25.86 seconds total
**Example_02:** 6.82 seconds total
**Example_03:** 6.72 seconds total

Example_02 and Example_03 were about 4x faster than Example_01.

---

## Task 1: Main Differences Between Executions

**Example_01 (Serial I/O):**
- Only rank 0 does alll the file reading and writing
- Uses MPI_Scatter ti distribute data and MPI_Gather to collect results
- Other processes just wait during I/O operations
- Creates a bottleneck on rank 0

**Example_02 (Independent Parallel I/O):**
- All processes read and write files at the same time
- Each process handles its own portion of data
- Uses MPI_File_open and MPI_File_write_at
- No scatter/gather needed

**Example_03 (Collective I/O with Hints):**
- Similar to Example_02 but uses collective operations (MPI_File_write_all)
- Adds MPI hints to optimize performance
- Uses aggregator processes to coordinate writes
- Better for large HPC systems

---

## Task 2: Execution Time Differences

**Reading times:**
- Example_01: 24.54 sec (only rank 0 reads)
- Example_02: 5.82 sec (all processes read)
- Example_03: 5.58 sec (all processes read)

The parallel versions are 4x faster because all 4 processes read simultaneously instead of just one.

**Writing times:**
- Example_01: 0.67 sec
- Example_02: 0.85 sec
- Example_03: 0.97 sec

Interestingly, Example_01 has the fastest write time because rank 0 writes everything in one sequential operation. Example_03 is slowest due to coordination overhead between processes.

**Why total time favors parallel I/O:**
Even though Example_01 writes faster, the reading time dominates. Spending 24 seconds reading vs 0.67 seconds writing means the slow reading kills performance.

---

## Task 3: Drastic Difference Between Example_01 and Example_02/03

The main problem with Example_01 is that rank 0 must allocate memory for ALL processes:

```c
// Rank 0 needs to store everyone's data:
double *all_temp = malloc(4 * 3,750,000 * sizeof(double));     // 120 MB
double *all_humidity = malloc(4 * 3,750,000 * sizeof(double)); // 120 MB
double *all_pressure = malloc(4 * 3,750,000 * sizeof(double)); // 120 MB
// Total: ~360 MB on one process
```

This works with 4 processes but would fail with 100 or 1000 processes - rank 0 would run out of memory.

Also, MPI_Scatter and MPI_Gather create network bottlenecks as all data flows through rank 0.

In Example_02/03, memory and I/O work is distributed across all processes, so it scales much better. That's why we get the 4x speedup - all processes working together instead of one doing everything.

---

## Task 4: Example_03 Improvements - MPI Hints

In Example_03 I found this hints function:

```c
void setup_hints(MPI_Info *info, int rank, int nprocs) {
    MPI_Info_create(info);
    MPI_Info_set(*info, "collective_buffering", "true");
    MPI_Info_set(*info, "cb_buffer_size", "16777216");
    MPI_Info_set(*info, "cb_nodes", "4");
    MPI_Info_set(*info, "romio_cb_write", "enable");
}
```

**What the hints do:**

`collective_buffering = true` - Makes some processes act as aggregators that collect data from others and write in larger chunks. Filesystems prefer big sequential writes.

`cb_buffer_size = 16777216` - Sets a 16 MB buffer for each aggregator to collect data before writing.

`cb_nodes = 4` - Number of aggregator processes. Should match filesystem configuration on HPC systems.

`romio_cb_write = enable` - Enables two-phase collective write algorithm where data gets redistributed and then written in large blocks.

**Why Example_03 wasn't faster on my machine:**

Example_03 actually had slower write time (0.97 sec vs 0.85 sec for Example_02). This is because:
- My laptop only has one diisk, not a parallel filesystem
- With just 4 processes, coordination overhead costs more than it saves
- Modern SSDs already handle random writes well

On a real HPC cluster with hundreds of processes and parallel filesystems like Lustre, Example_03 would be much faster because the aggregation would combine many small writes into fewer large writes across multiple storage servers.

---

## Task 5: Comparison Example_02 vs Example_03

**When to use Example_02:**
- Small number of processes
- Local filesystem or development machine
- Simpler code

**When to use Example_03:**
- Large scale (100+ processes)
- HPC cluster with parallel filesystem
- Production workloads

**My results:**
Example_02: 6.82 sec
Example_03: 6.72 sec

On my machine they're basically the same. Example_02 is slightly faster for writing (0.85 vs 0.97 sec).

But on an HPC system with many processes, Example_03's collective I/O would be significantly faster because the hints and aggregation would optimize for the parallel filesystem.

**Conclusion:** Use Example_02 for small-scale work, Example_03 for large HPC systems.

---

## What I Learned

1. Serial I/O doesn't scale - Example_01 was 4x slower and would crash with many processes

2. Parallel I/O makes a big difference when all processes can read/write simultaneously

3. Optimizations like MPI hints need the right environment - they didn't help on my laptop but would on HPC clusters

4. File I/O can be a major bottleneck - in Example_01 almost all time was spent on reading

Parallel I/O is important for HPC applications because even if your computation is fast, you'll waste time if file operations aren't parallelized.

---
