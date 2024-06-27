#include "GenData.h"
#include "CreateEle.h"
#include "Compare.h"
#include "Runtime.h"

string transferSort(string a) {
    if (a == "shell-sort") return "Shell Sort";
    else if (a == "insertion-sort") return "Insertion Sort";
    else if (a == "shaker-sort") return "Shaker Sort";
    else if (a == "counting-sort") return "Counting Sort";
    else return "Unknown Sort";
}

void writeData(const string& fileName, int* arr, int n) {
    ofstream outputFile(fileName, ios::app);
    if (!outputFile) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }
    outputFile << n << endl;
    for (int i = 0; i < n; ++i) {
        outputFile << arr[i] << " ";
    }
    outputFile << endl;
    outputFile.close();
}

// Function to load data from a file
void LoadDataFromFile(const string& fileName, int*& arr, int& n, bool& fileOpened) {
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Error opening file: " << fileName << endl;
        fileOpened = false;
        return;
    }
    fileOpened = true;
    inputFile >> n;
    arr = new int[n];
    for (int i = 0; i < n; ++i) {
        inputFile >> arr[i];
    }
    inputFile.close();
}

void SortAndMeasure(const string& sortType, int arr[], int n, bool measureTime, bool measureComp, long long& count, double& time) {
    int* inputArr1 = new int[n];
    int* inputArr2 = new int[n];
    memcpy(inputArr1, arr, n * sizeof(int));
    memcpy(inputArr2, arr, n * sizeof(int));

    count = 0;
    time = 0.0;

    if (sortType == "insertion-sort") {
        if (measureComp) insertionSortC(inputArr1, n, count);
        if (measureTime) insertionSortR(inputArr2, n, time);
        writeData("output.txt", inputArr1, n);
    }
    else if (sortType == "shaker-sort") {
        if (measureComp) shakerSortC(inputArr1, n, count);
        if (measureTime) shakerSortR(inputArr2, n, time);
        writeData("output.txt", inputArr1, n);
    }
    else if (sortType == "shell-sort") {
        if (measureComp) shellSortC(inputArr1, n, count);
        if (measureTime) shellSortR(inputArr2, n, time);
        writeData("output.txt", inputArr1, n);
    }
    else if (sortType == "counting-sort") {
        if (measureComp) countingSortC(inputArr1, n, count);
        if (measureTime) countingSortR(inputArr2, n, time);
        writeData("output.txt", inputArr1, n);
    }
    else {
        cout << "Unknown sort type: " << sortType << endl;
        delete[] inputArr1;
        delete[] inputArr2;
        return;
    }

    delete[] inputArr1;
    delete[] inputArr2;
}

void GenerateAndMeasureForAll(const string& algorithm, int n, const string& outputParam) {
    // Array to hold generated data
    int* arr;

    if (outputParam != "-time" && outputParam != "-both" && outputParam == "comp") {
        cout << "Invalid output mode";
        return;
    }

    long long count = 0;
    double time = 0;
    // Measure time or comparisons or both based on outputParam
    bool measureTime = (outputParam == "-time" || outputParam == "-both");
    bool measureComp = (outputParam == "-comp" || outputParam == "-both");

    // Generate and measure for randomized data
    arr = new int[n];
    GenerateRandomData(arr, n);
    cout << "Input order: Randomized Data:" << endl;
    cout << "_______________________" << endl; 
    writeData("input_1.txt", arr, n);
    SortAndMeasure(algorithm, arr, n, measureTime, measureComp, count, time);
  
    delete[] arr;
    if (measureTime) cout << "Running time:" << time * 1000 << " miliseconds" << endl;
    if (measureComp) cout << "Comparisons:" << count << endl;
    cout << endl;

    count = 0;
    time = 0.0;

    // Generate and measure for nearly sorted data
    arr = new int[n];
    GenerateNearlySortedData(arr, n);
    cout << "Input order: Nearly Sorted Data:" << endl;
    cout << "_______________________" << endl;
    writeData("input_2.txt", arr, n);
    SortAndMeasure(algorithm, arr, n, measureTime, measureComp, count, time);
 
    delete[] arr;
    if (measureTime) cout << "Running time:" << time * 1000 << " miliseconds" << endl;
    if (measureComp) cout << "Comparisons:" << count << endl;
    cout << endl;

    // Generate and measure for sorted data
    arr = new int[n];
    GenerateSortedData(arr, n);
    cout << "Input order: Sorted Data:" << endl;
    cout << "_______________________" << endl;
    writeData("input_3.txt", arr, n);
    SortAndMeasure(algorithm, arr, n, measureTime, measureComp, count, time);

    delete[] arr;
    if (measureTime) cout << "Running time:" << time * 1000 << " miliseconds" << endl;
    if (measureComp) cout << "Comparisons:" << count << endl;
    cout << endl;

    // Generate and measure for reverse sorted data
    arr = new int[n];
    GenerateReverseData(arr, n);
    cout << "Input order: Reverse Sorted Data:" << endl;
    cout << "_______________________" << endl;
    writeData("input_4.txt", arr, n);
    SortAndMeasure(algorithm, arr, n, measureTime, measureComp, count, time);
  
    delete[] arr;
    if (measureTime) cout << "Running time:" << time * 1000 << " miliseconds" << endl;
    if (measureComp) cout << "Comparisons:" << count << endl;
    cout << endl;

}
