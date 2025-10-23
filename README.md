# Assignment 3 - AoSoA Performance


In this assignment I worked on testing how data layout and memory affect program speed.  
I used something called AoSoA (Array of Structures of Arrays), which helps make the program faster by organizing data in a better way for the processor and cache.

The goal was to test how performance changes when I use different vector sizes (V) and different dataset sizes (N).  
I used C++, Makefile and WSL (Ubuntu) to run everything and collect results.

Some parts of the code in `aosoa_measurement.cpp` were empty and I had to finish them.  
I needed to add a few lines that made the program actually do the work.  


After finishing the missing code, I used the Makefile that was already in the folder to run the tests.  
I just opened the terminal and used these commands:
make test_1K
make test_10K
make test_100K
make test_1M
make test_10M

For small datasets like 1K or 10K, there was almost no difference between vector sizes because everything fits in the cache and runs fast.

When the datasets got bigger (like 100K, 1M and 10M), I started seeing more difference.


Google Sheets link:
https://docs.google.com/spreadsheets/d/1QcQjiL2rGZk5sIAQ_jLbfWElKRQpoMppn52Bq3e1Amc/edit?usp=sharing

Graph image:
![Performance Graph](graph.png)
