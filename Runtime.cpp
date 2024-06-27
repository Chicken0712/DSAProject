#include "Runtime.h"

// Insertion Sort algorithm
void insertionSortR(int a[], int n, double& time) {
    auto start = chrono::high_resolution_clock::now();
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    time = duration.count();
}

// Shaker Sort algorithm with runtime measurement
void shakerSortR(int a[], int n, double& time) {
    auto start = chrono::high_resolution_clock::now();
    bool swapped = true;
    int startIdx = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = startIdx; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;
        --end;

        for (int i = end - 1; i >= startIdx; --i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        ++startIdx;
    }
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end_time - start;
    time = duration.count();
}

// Shell Sort algorithm with runtime measurement
void shellSortR(int arr[], int n, double& time) {
    auto start = chrono::high_resolution_clock::now();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    time = duration.count();
}

// Counting Sort algorithm with runtime measurement
void countingSortR(int arr[], int n, double& time) {
    if (n <= 1) return;
    auto start = chrono::high_resolution_clock::now();

    int maxVal = arr[0], minVal = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxVal) maxVal = arr[i];
        if (arr[i] < minVal) minVal = arr[i];
    }

    int range = maxVal - minVal + 1;
    int* count = new int[range]();

    for (int i = 0; i < n; ++i) {
        count[arr[i] - minVal]++;
    }

    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }

    int* output = new int[n];
    for (int i = n - 1; i >= 0; --i) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    time = duration.count();
}
