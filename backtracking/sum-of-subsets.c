#include <stdio.h>

#define MAX 20

int weights[MAX];        // input elements
int solution[MAX];       // 1 = included, 0 = excluded
int num_elements;        // total elements
int target_sum;          // required sum
int found = 0;           // tracks if any subset is found

// prints the current valid subset
void print_subset()
{
    printf("Subset: ");
    for (int i = 0; i < num_elements; i++)
    {
        if (solution[i] == 1)
            printf("%d ", weights[i]);
    }
    printf("\n");

    found = 1;  // mark that at least one solution exists
}

// backtracking function
void sum_of_subsets(int current_sum, int index, int remaining_sum)
{
    if (index >= num_elements)
        return;  // prevent out-of-bounds

    solution[index] = 1;  // include current element

    if (current_sum + weights[index] == target_sum)
    {
        print_subset();  // valid subset found
    }
    else if (index + 1 < num_elements &&
             current_sum + weights[index] + weights[index + 1] <= target_sum)
    {
        // explore further only if next inclusion is feasible
        sum_of_subsets(current_sum + weights[index],
                       index + 1,
                       remaining_sum - weights[index]);
    }

    // check if excluding current element can still lead to solution
    if (index + 1 < num_elements &&
        (current_sum + remaining_sum - weights[index] >= target_sum) &&
        (current_sum + weights[index + 1] <= target_sum))
    {
        solution[index] = 0;  // exclude current element

        sum_of_subsets(current_sum,
                       index + 1,
                       remaining_sum - weights[index]);
    }
}

int main()
{
    int total_sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &num_elements);

    printf("Enter elements: ");
    for (int i = 0; i < num_elements; i++)
    {
        scanf("%d", &weights[i]);
        total_sum += weights[i];  // compute total sum for pruning
    }

    printf("Enter required sum: ");
    scanf("%d", &target_sum);

    for (int i = 0; i < num_elements; i++)
        solution[i] = 0;  // initialize solution array

    // input should ideally be sorted for correct pruning behavior
    sum_of_subsets(0, 0, total_sum);

    if (!found)
        printf("No subset found.\n");

    return 0;
}
