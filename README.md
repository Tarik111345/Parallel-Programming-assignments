# Parallel-Programming-assignments


tudent@itcenter-lab128:~/Parallel-Programming-assignments$ make
gcc      -Wall -Wextra -g -std=c99 -o memory_demo main.c
main.c: In function ‘main’:
main.c:8:43: warning: ‘ipos’ may be used uninitialized [-Wmaybe-uninitialized]
    8 |    for (int i = 0; i<=10; i++){ iarray[i] = ipos; }
      |                                 ~~~~~~~~~~^~~~~~
student@itcenter-lab128:~/Parallel-Programming-assignments$ make
make: Nothing to be done for 'all'.
student@itcenter-lab128:~/Parallel-Programming-assignments$ make
make: Nothing to be done for 'all'.
student@itcenter-lab128:~/Parallel-Programming-assignments$ make
make: Nothing to be done for 'all'.
student@itcenter-lab128:~/Parallel-Programming-assignments$ make
make: Nothing to be done for 'all'.
student@itcenter-lab128:~/Parallel-Programming-assignments$ make valgrind
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./memory_demo
==9299== Memcheck, a memory error detector
==9299== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==9299== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==9299== Command: ./memory_demo
==9299== 
==9299== Invalid write of size 4
==9299==    at 0x1091C6: main (main.c:8)
==9299==  Address 0x4a9e068 is 0 bytes after a block of size 40 alloc'd
==9299==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==9299==    by 0x109185: main (main.c:6)
==9299== 
==9299== Conditional jump or move depends on uninitialised value(s)
==9299==    at 0x1091F4: main (main.c:10)
==9299==  Uninitialised value was created by a stack allocation
==9299==    at 0x109169: main (main.c:4)
==9299== 
==9299== Invalid read of size 4
==9299==    at 0x1091EF: main (main.c:10)
==9299==  Address 0x4a9e068 is 0 bytes after a block of size 40 alloc'd
==9299==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==9299==    by 0x109185: main (main.c:6)
==9299== 
==9299== 
==9299== HEAP SUMMARY:
==9299==     in use at exit: 40 bytes in 1 blocks
==9299==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==9299== 
==9299== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==9299==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==9299==    by 0x109185: main (main.c:6)
==9299== 
==9299== LEAK SUMMARY:
==9299==    definitely lost: 40 bytes in 1 blocks
==9299==    indirectly lost: 0 bytes in 0 blocks
==9299==      possibly lost: 0 bytes in 0 blocks
==9299==    still reachable: 0 bytes in 0 blocks
==9299==         suppressed: 0 bytes in 0 blocks
==9299== 
==9299== For lists of detected and suppressed errors, rerun with: -s
==9299== ERROR SUMMARY: 14 errors from 4 contexts (suppressed: 0 from 0)
student@itcenter-lab128:~/Parallel-Programming-assignments$ ^C
student@itcenter-lab128:~/Parallel-Programming-assignments$ make valgrind
gcc      -Wall -Wextra -g -std=c99 -o memory_demo main.c
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./memory_demo
==9527== Memcheck, a memory error detector
==9527== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==9527== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==9527== Command: ./memory_demo
==9527== 
==9527== 
==9527== HEAP SUMMARY:
==9527==     in use at exit: 0 bytes in 0 blocks
==9527==   total heap usage: 1 allocs, 1 frees, 40 bytes allocated
==9527== 
==9527== All heap blocks were freed -- no leaks are possible
==9527== 
==9527== For lists of detected and suppressed errors, rerun with: -s
==9527== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)




Objasnjenje:

in the task a program is created that uses dynamic memory and works with an array of integers. The program makes space for 10 elementsm it fills array with a value, checks is there a certain value in the array.

Error because ipos was used before being initialized. In the for loop the i <=10 was used which led to writitng outside the bounds of array, we need from 0 to 9. The memory allocated using malloc was not freedat the end of the prog, which valgrind reported as mem leak.

I initialized ipos to -1 and changed in the loop to i < 10 and free(iarray) was added to realese the all memory. After valgrid reported no errors,

