#include <iostream>
#include <omp.h>

using namespace std;

void parallel_bubble_sort(int arr[], int n) {
    for (int j = 0; j < n - 1; j++) {
        #pragma omp parallel for
        for (int i = 0; i < n - 1 - j; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
            }
        }
    }
}

int main() {
    int n;

    cout << "Enter total number of elements: ";
    cin >> n;

    int *arr = new int[n]; // Dynamic array allocation

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    parallel_bubble_sort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr; // Free allocated memory

    return 0;
}
