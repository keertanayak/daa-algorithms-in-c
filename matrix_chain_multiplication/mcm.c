#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 20

// dp tables
int cost_table[MAX][MAX];
int split_table[MAX][MAX];

// compute optimal cost using dynamic programming
void matrix_chain_order(int dims[], int n) {
    for (int i = 1; i <= n; i++)
        cost_table[i][i] = 0;

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            cost_table[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = cost_table[i][k] + cost_table[k + 1][j]
                         + dims[i - 1] * dims[k] * dims[j];

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
    if (i == j) {
        printf("M%d", i);
        return;
    }

    printf("(");
    print_parenthesis(i, split_table[i][j]);
    print_parenthesis(split_table[i][j] + 1, j);
    printf(")");
}

// print dp tables
void print_table(int table[MAX][MAX], int n, char name) {
    printf("\n%c table:\n", name);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
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

    int n = 10;
    int dims[11];

    printf("Matrix Chain Multiplication\n\n");

    printf("Generated dimensions:\n");
    for (int i = 0; i <= n; i++) {
        dims[i] = 1 << (rand() % 4 + 1);
        printf("%d ", dims[i]);
    }
    printf("\n");
    matrix_chain_order(dims, n);

    print_table(cost_table, n, 'm');
    print_table(split_table, n, 's');

    printf("\nOptimal Parenthesization:\n");
    print_parenthesis(1, n);
    printf("\n");

    return 0;
}
