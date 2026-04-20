# Matrix Chain Multiplication (Dynamic Programming)

## Problem Statement

Implement Matrix Chain Multiplication (MCM) using Dynamic Programming to determine the most efficient way to multiply a sequence of matrices.

Given a chain of matrices M1 × M2 × ... × M10, where the dimensions are stored in an array p[0..10] such that matrix Mi has dimensions p[i-1] × p[i], the goal is to minimize the total number of scalar multiplications.

The dimensions are randomly generated as powers of 2, and matrix elements can take values between 0 and 1.

## Objectives

* Compute the cost table m[i][j] representing minimum multiplications
* Compute the split table s[i][j] representing optimal parenthesization
* Determine the optimal order of matrix multiplication

## Approach

Dynamic Programming is used to break the problem into smaller subproblems.
The solution stores intermediate results in tables to avoid redundant computations.

## Time Complexity

O(n^3)

## Space Complexity

O(n^2)

## Sample Output

* Cost table showing minimum multiplication costs
* Split table showing optimal split positions
* Optimal parenthesization of matrices

## Key Insight

The problem exhibits:

* Optimal substructure
* Overlapping subproblems

This allows an exponential problem to be reduced to polynomial time.

## How to Run

gcc mcm.c -o mcm

./mcm
