#include "Compare.h"
using namespace std;

// Insertion Sort algorithm with comparison count
void insertionSortC(int a[], int n, long long& compareCount)
{
    compareCount = 0;  // Initialize comparison count
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && (++compareCount && a[j] > key)) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

// Shaker (Cocktail) Sort algorithm with comparison count
void shakerSortC(int a[], int n, long long& compareCount)
{
    compareCount = 0;  // Initialize comparison count
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {  // Forward pass
            if (++compareCount && a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;  // Set swapped flag
            }
        }

        if (!swapped)
            break;

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {  // Backward pass
            if (++compareCount && a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;  // Set swapped flag
            }
        }
        ++start;  // Move start pointer
    }
}

// Shell Sort algorithm with comparison count
void shellSortC(int a[], int n, long long& compareCount)
{
    compareCount = 0;  // Initialize comparison count
    for (int gap = n / 2; gap > 0; gap /= 2) {  // Reduce gap size until it's 1
        for (int i = gap; i < n; i += 1) {  // Perform insertion sort for current gap
            int temp = a[i];  // Store current element in temp
            int j;
            for (j = i; j >= gap && (++compareCount && a[j - gap] > temp); j -= gap) {
                a[j] = a[j - gap];  // Shift elements right
            }
            a[j] = temp;  // Place temp in correct position
        }
    }
}

// Counting Sort algorithm with comparison count
void countingSortC(int a[], int n, long long& compareCount) {
    compareCount = 0;  // Initialize comparison count

    if (n <= 1) return;  // Base case: already sorted or single element

    int maxVal = a[0], minVal = a[0];
    for (int i = 1; i < n; ++i) {  // Find min and max values in array
        if (++compareCount && a[i] > maxVal) maxVal = a[i];
        if (++compareCount && a[i] < minVal) minVal = a[i];
    }

    int range = maxVal - minVal + 1;
    int* count = new int[range]();  // Initialize count array with zeros

    for (int i = 0; i < n; ++i) {  // Count occurrences of each element
        count[a[i] - minVal]++;  // Increment count for current element
    }

    for (int i = 1; i < range; ++i) {  // Modify count array to reflect positions in output array
        count[i] += count[i - 1];  // Cumulative sum of counts
    }

    int* output = new int[n];

    for (int i = n - 1; i >= 0; --i) {
        output[count[a[i] - minVal] - 1] = a[i];  // Place elements in output array
        count[a[i] - minVal]--;  // Decrement count for current element
    }

    for (int i = 0; i < n; ++i) {
        a[i] = output[i];  // Copy sorted elements back to original array
    }

    delete[] count;
    delete[] output;
}