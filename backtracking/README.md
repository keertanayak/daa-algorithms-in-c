# Sum of Subsets (Backtracking)

## Problem Statement

Implement the Sum of Subsets problem using the Backtracking approach.

Given `n` distinct positive integers and a target sum `m`, find all possible subsets whose sum is equal to `m`.

---

## Objective

* Generate all subsets whose sum equals the target value
* Apply backtracking with pruning to avoid unnecessary computations
* Print all valid subsets

---

## Approach

The problem is solved using **Backtracking**, where each element has two choices:

* Include the element in the subset
* Exclude the element from the subset

A recursive approach is used to explore all possible combinations.
Pruning conditions are applied to stop exploring paths that cannot lead to a valid solution.

---

## Time Complexity

* Worst Case: **O(2ⁿ)**

---

## Space Complexity

* **O(n)** (recursion stack + solution array)

---

## Sample Output

```
Enter number of elements: 4
Enter elements: 2 4 6 8
Enter required sum: 8

Subset: 2 6
Subset: 8
```

---

## Key Insight

The problem demonstrates:

* Backtracking using recursion
* State-space tree exploration
* Pruning to reduce unnecessary computations

The efficiency improves significantly when the input is **sorted**, as it helps in better pruning.

---

## How to Run

```bash
gcc sum-of-subsets.c -o sum
./sum
```

---

