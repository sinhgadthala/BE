#include <iostream>
#include <stdlib.h>  // For malloc() and free()
#include <omp.h>
#include <climits>

using namespace std;

void min_reduction(int* arr, int n) {
    int min_value = INT_MAX;
    
    #pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    
    cout << "Minimum value: " << min_value << endl;
}

void max_reduction(int* arr, int n) {
    int max_value = INT_MIN;
    
    #pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    
    cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(int* arr, int n) {
    int sum = 0;
    
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    cout << "Sum: " << sum << endl;
}

void average_reduction(int* arr, int n) {
    int sum = 0;
    
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    cout << "Average: " << (double)sum / n << endl;  // Fixed: Use 'n' instead of 'n-1'
}

int main() {
    int n;
    
    cout << "\nEnter total number of elements: ";
    cin >> n;

    int* arr = (int*)malloc(n * sizeof(int));  // Dynamic memory allocation

    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    double start = omp_get_wtime();

    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);

    double stop = omp_get_wtime();

    cout << "Execution Time: " << (stop - start) << " seconds\n";

    free(arr);  // Free dynamically allocated memory

    return 0;
}
