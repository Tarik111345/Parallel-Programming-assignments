## Lab: MPI Partial Sum 

## Lab Objective
The goal of this lab was to understand how **MPI (Message Passing Interface)** works and how I can run a program across multiple processes. During this lab I learned to:  
- Initialize and finalize MPI programs (MPI_Init, MPI_Finalize)  
- Get the rank of each process and the total number of processes  
- Avoidd deadlocks using the correct order for send/receive  
- Use collective communication (MPI_Scatter, MPI_Reduce, MPI_Bcast)  
- Distribute dta, calculate partial sums, and combine results  

I used the provided Makefile and ran:
- make
This compiled PartialSum.c and timer.c and createdd the executable PartialSum.

## How I Ran the Program
I ran the program with different nummbers of processes to see the difference:
- mpirun -n 2 ./PartialSum
- mpirun -n 4 ./PartialSum
- mpirun -n 8 ./PartialSum

On my computer I could run all three.

## My Results:

# 2 Processes
Rank 0: processed 5000 elements, partial sum = 12502500.00
Rank 1: processed 5000 elements, partial sum = 37502500.00
Scatter time: 0.000301 s
Reduce time:  0.000315 s
Total sum: 50005000.00

# 4 Processes
Rank 0: processed 2500 elements, partial sum = 3126250.00
Rank 1: processed 2500 elements, partial sum = 9376250.00
Rank 2: processed 2500 elements, partial sum = 15626250.00
Rank 3: processed 2500 elements, partial sum = 21876250.00
Scatter time: 0.000031 s
Reduce time:  0.000015 s
Total sum: 50005000.00

# 8 Processes
Rank 0: processed 1250 elements, partial sum = 2344375.00
Rank 1: processed 1250 elements, partial sum = 3906875.00
Rank 2: processed 1250 elements, partial sum = 5469375.00
Rank 3: processed 1250 elements, partial sum = 7031875.00
Rank 4: processed 1250 elements, partial sum = 8594375.00
Rank 5: processed 1250 elements, partial sum = 10156875.00
Rank 6: processed 1250 elements, partial sum = 11719375.00
Rank 7: processed 1250 elements, partial sum = 12505000.00
Total sum: 50005000.00


- Using MPI_Scatter, the array was divded between all processes.

- Each proces calculated its partial sum.

- Then MPI_Reduce combined all the partial sums into the final total.

- More processes means each process does less work, so compute time per process is smaller.

- The total sum is always correct (50005000) no matter how many processes I used.



- The number of processes must divide the array evenly to avoid issues.

- To prevent deadlocks, I learned that non-blocking calls (MPI_Isend, MPI_Irecv) or alternating send/recv by rank can help.

- Time measurements show that collective operations are very fast.