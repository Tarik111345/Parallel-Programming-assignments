Global Sum Precision and Runtime Analysis 

In this assignment i tested different ways to calculate the sum of numbers and see hpw much error theu make and how fast they are.
This is part of the global sum problem, which happens because floating-point numbers are not perfectly accurate — when you add many numbers, the result can slightly change depending on the order of addition.

Methods
I used four different summation methods:
- Long double – uses higher precision (more digits) than normal double.
- Pairwise summation – adds numbers in pairs to make results more stable.
- Kahan summation – corrects lost precision by tracking small rounding errors.
- Knuth summation – similar to Kahan but a bit faster.

How it was tested 
- Usedf arrays with sizes from 2^10 to 2^23 
- Galf of numbers were big, half very small (Leblanc problem).
- I checked how big error was and how long eeach method took to run.
make 
make run

FUll results of all tests are in my Excel file:
https://docs.google.com/spreadsheets/d/1okIJJG9BQ-mLJFNHoQn590qgU8sJW0dYpLYUVgwT74c/edit?usp=sharing

Conclusion
- Pairwise and Knuth are the best mix of speed and accuracy.
- Kahan is the most precisse, but it’s slower.
- Long double helps, but not perfect.