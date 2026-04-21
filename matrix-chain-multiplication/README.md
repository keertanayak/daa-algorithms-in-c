# Matrix Chain Multiplication (Dynamic Programming)

## Problem Statement

Implement Matrix Chain Multiplication (MCM) using Dynamic Programming to determine the most efficient way to multiply a sequence of matrices.

Given a chain of matrices ( M_1 \times M_2 \times \dots \times M_n ), where the dimensions are stored in an array `p[0..n]` such that matrix ( M_i ) has dimensions `p[i-1] × p[i]`, the goal is to minimize the total number of scalar multiplications.

---

## Objective

* Compute the cost table `m[i][j]` representing minimum multiplication cost
* Compute the split table `s[i][j]` representing optimal split positions
* Determine the optimal parenthesization of matrix multiplication

---

## Approach

The problem is solved using **Dynamic Programming**, where the solution is built by solving smaller subproblems and storing their results.

* Each subproblem computes the minimum cost of multiplying matrices from index `i` to `j`
* All possible split points `k` between `i` and `j` are evaluated
* The minimum cost is stored and reused to avoid recomputation

---

## Time Complexity

* **O(n³)**
  (due to three nested loops over chain length, start index, and split point)

---

## Space Complexity

* **O(n²)**
  (for storing cost and split tables)

---

## Sample Output

```text
Matrix Chain Multiplication

Generated dimensions:
2 4 8 2 4 2 8 4 2 4 8

m table:
...

s table:
...

Optimal Parenthesization:
((M1(M2M3))((M4M5)(M6(M7(M8M9)))))
```

---

## Key Insight

The problem demonstrates:

* Optimal substructure
* Overlapping subproblems

Dynamic Programming reduces the exponential number of ways to parenthesize matrices to a polynomial-time solution.

---

## How to Run

```bash
gcc mcm.c -o mcm
./mcm
```

---


