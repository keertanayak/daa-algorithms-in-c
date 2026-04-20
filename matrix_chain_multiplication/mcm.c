#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 20

// dp tables
int cost_table[MAX][MAX];   // stores minimum multiplication cost
int split_table[MAX][MAX];  // stores index where optimal split occurs

// compute optimal cost using dynamic programming
void matrix_chain_order(int dims[], int n) {
    // cost is zero when multiplying one matrix
    for (int i = 1; i <= n; i++)
        cost_table[i][i] = 0;

    // len represents chain length (number of matrices in subproblem)
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;

            // initialize with maximum possible value
            cost_table[i][j] = INT_MAX;

            // try all possible split points
            for (int k = i; k < j; k++) {

                // cost = cost of left + cost of right + cost of multiplying two results
                int cost = cost_table[i][k] + cost_table[k + 1][j]
                         + dims[i - 1] * dims[k] * dims[j];

                // update minimum cost and store split position
                if (cost < cost_table[i][j]) {
                    cost_table[i][j] = cost;
                    split_table[i][j] = k;
                }
            }
        }
    }
}

// print optimal parenthesization
void print_parenthesis(int i, int j) {
    // base case: single matrix
    if (i == j) {
        printf("M%d", i);
        return;
    }

    // recursively print left and right subchains
    printf("(");
    print_parenthesis(i, split_table[i][j]);           // left part
    print_parenthesis(split_table[i][j] + 1, j);       // right part
    printf(")");
}

// print dp tables
void print_table(int table[MAX][MAX], int n, char name) {
    printf("\n%c table:\n", name);

    // print table in matrix form
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {

            // lower triangular part is unused
            if (j < i)
                printf("0\t");
            else
                printf("%d\t", table[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(2024);

    int n = 10;        // number of matrices
    int dims[11];      // dimensions array (size n+1)

    printf("Matrix Chain Multiplication\n\n");

    printf("Generated dimensions:\n");

    // generate random dimensions (powers of 2 for simplicity)
    for (int i = 0; i <= n; i++) {
        dims[i] = 1 << (rand() % 4 + 1);
        printf("%d ", dims[i]);
    }
    printf("\n");

    // compute dp solution
    matrix_chain_order(dims, n);

    // display cost and split tables
    print_table(cost_table, n, 'm');
    print_table(split_table, n, 's');

    printf("\nOptimal Parenthesization:\n");

    // print optimal multiplication order
    print_parenthesis(1, n);

    printf("\n");

    return 0;
}
