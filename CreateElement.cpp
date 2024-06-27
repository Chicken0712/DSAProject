#include "CreateEle.h"

void GenerateRandomData(int a[], int n)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % n;
    }
}

void GenerateSortedData(int a[], int n)
{
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
}

void GenerateReverseData(int a[], int n)
{
    for (int i = 0; i < n; i++) {
        a[i] = n - 1 - i;
    }
}

void GenerateNearlySortedData(int a[], int n)
{
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++) {
        int r1 = rand() % n;
        int r2 = rand() % n;
        swap(a[r1], a[r2]);
    }
}

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}