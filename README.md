# Assignment 2
> Course Code: **CIS\*3490**
> Author: **Joel Harder**
> Last Edited: **February 13, 2023**

## Description

#### Problem 1 - Counting Inversions
> A brute force and a recursive algorithm to count the number of inversions in an array of distinct numbers. An inversion is a pair of array elements that are out of order, i.e., `A[i] > A[j]` for `i < j`. The number of inversions reflects how far the array is from being sorted. The programs will prompt for a file to read from and then print the number of inversions.

`P11.c` - A brute force algorithm to count the number of inversions in an array and analyze the number of repetitions of its basic operation.
`P12.c` - A recursive divide-and-conquor algorithm of `Θ(n log n)` to count the number of inversion in an array and set up a recurrence to analyze the number of repetitions of its basic operation of the best case.

Files must be a list of integers seperated by spaces, with 5 integers per row. Use `data_P1.txt` as an example.

#### Problem 2 - Convex Hull (Shortest Path Around)
> A brute force and a recursive algorithm to find the shortest path around a set of given points. The set of points for the programs can be found in `data_A2_Q2.txt`. Programs will prompt you for a file to read from and then print the x-y coordinates of hull points as it identifies them. After constructing the convex hull, each program will prompt for two hull points; `s1` and `s2`. It will then calculate and print the shortest path around the hull from point `s1` to point `s2`.

`P21.c` - A brute force algorithm to solve the shortest path around problem.
`P22.c` - A recursive divide-and-conquer algorithm of `Θ(n log n)` to solve the shortest path around problem and set up a recurrence to analyze the number of repetitions of the basic operation to compute the hull for the best case.

Files must be a list of floating point numbers with each row being one set of (x,y) coordinates. There is an example file `data_P2.txt` that you may use.

## Compiling
To compile all programs type
```
make all
```

<br>To compile individual programs type
```
make P<problem number>
```

## Running
To run any program type
```
./P<problem number>
```