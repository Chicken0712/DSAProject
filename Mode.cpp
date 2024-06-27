#include "CreateEle.h"
#include "GenData.h"
#include "Mode.h"

string transferMode(string a) {
    if (a == "-rand") return "Randomized Data";
    else if (a == "-sorted") return "Sorted Data";
    else if (a == "-nsorted") return "Nearly Sorted Data";
    else if (a == "-rev") return "Reversed Data";
    else return "Unknown Mode";
}

void RunAlgorithmMode(int argc, char* argv[]) {
    if (argc != 5 && argc != 6) {
        cout << "Invalid input for Algorithm mode";
        return;
    }

    string algorithm = argv[2];
    string param1 = argv[3];

    // Check if param1 is an integer (Command 2 or Command 3)
    bool isNumeric = all_of(param1.begin(), param1.end(), ::isdigit);

    if (isNumeric) {
        // Command 2 or Command 3
        int n = stoi(param1);
        string param2 = argv[4];

        if (argc == 6) {
            // Command 2: Run algorithm on data generated automatically
            int* arr = new int[n];

            if (param2 == "-rand") {
                GenerateRandomData(arr, n);
                writeData("input.txt", arr, n);
            }
            else if (param2 == "-nsorted") {
                GenerateNearlySortedData(arr, n);
                writeData("input.txt", arr, n);
            }
            else if (param2 == "-sorted") {
                GenerateSortedData(arr, n);
                writeData("input.txt", arr, n);
            }
            else if (param2 == "-rev") {
                GenerateReverseData(arr, n);
                writeData("input.txt", arr, n);
            }
            else {
                cout << "Unknown input order: " << param2 << endl;
                delete[] arr;
                return;
            }



            // Handle output parameters
            bool measureTime = false;
            bool measureComp = false;
            string param = argv[5];
            if (param == "-time") {
                measureTime = true;
            }
            else if (param == "-comp") {
                measureComp = true;
            }
            else if (param == "-both") {
                measureTime = true;
                measureComp = true;
            }
            else {
                cout << "Invalid mode for measuring" << endl;
                return;
            }

            double time = 0.0;
            long long count = 0;

            
            SortAndMeasure(algorithm, arr, n, measureTime, measureComp, count, time);
            delete[] arr;
            
            cout << "Input size: " << n << endl;
            cout << "Input order: " << transferMode(argv[4]) << endl;

            cout << "_______________________" << endl;

            if (measureTime) cout << "Running time:" << time * 1000 << " miliseconds" << endl;
            if (measureComp) cout << "Comparisons:" << count << endl;
 
        }

        else if (argc == 5) {
            // Command 3: Run algorithm on ALL data arrangements of a specified size
         
            cout << "Input size: " << n << endl;
            GenerateAndMeasureForAll(algorithm, n, param2);
            
        }
    }
    else {
        if (argc == 5) {
            // Command 1: Run algorithm on given input file
            string inputFileName = argv[3];
            string param2 = argv[4];

            bool measureTime = false;
            bool measureComp = false;
            if (param2 == "-time") {
                measureTime = true;
            }
            else if (param2 == "-comp") {
                measureComp = true;
            }
            else if (param2 == "-both") {
                measureTime = true;
                measureComp = true;
            }
            else {
                cout << "Invalid mode for measuring" << endl;
                return;
            }

            int* arr;
            int n;
            bool fileOpened;
            double time = 0.0;
            long long count = 0;

            LoadDataFromFile(inputFileName, arr, n, fileOpened);
            if (!fileOpened) return;
            cout << endl;
            SortAndMeasure(algorithm, arr, n, measureTime, measureComp, count, time);
            delete[] arr;
    
            cout << "Input file:" << argv[3] << endl;
            cout << "Input size:" << n << endl;
            
            cout << "_______________________" << endl;

            if (measureTime) cout << "Running time:" << time * 1000 << " miliseconds" << endl;
            if (measureComp) cout << "Comparisons:" << count << endl;
        }
        else {
            cout << "Invalid syntax for reading file input" << endl;
            return;
        }
    }
}

// Function to handle Comparison mode
void RunComparisonMode(int argc, char* argv[]) {
    if (argc != 5 && argc != 6) {
        cout << "Invalid input for Comparison mode";
        return;
    }

    string algorithm1 = argv[2];
    string algorithm2 = argv[3];
    string param1 = argv[4];
    string param2;
    if (argc == 6) param2 = argv[5];
    else param2 = ' ';

    if (argc == 6) {
        // Run both algorithms on data generated automatically
        int n = stoi(param1);
        int* arr = new int[n];

        if (param2 == "-rand") {
            GenerateRandomData(arr, n);
            writeData("input.txt", arr, n);
        }
        else if (param2 == "-nsorted") {
            GenerateNearlySortedData(arr, n);
            writeData("input.txt", arr, n);
        }
        else if (param2 == "-sorted") {
            GenerateSortedData(arr, n);
            writeData("input.txt", arr, n);
        }
        else if (param2 == "-rev") {
            GenerateReverseData(arr, n);
            writeData("input.txt", arr, n);
        }
        else {
            cout << "Unknown input order: " << param2 << endl;
            delete[] arr;
            return;
        }

        bool measureTime = true; // Assuming we always measure time in comparison mode
        bool measureComp = true;

        double time1 = 0.0;
        double time2 = 0.0;
        long long count1 = 0;
        long long count2 = 0;
        // Run sorting algorithms
        SortAndMeasure(algorithm1, arr, n, measureTime, measureComp, count1, time1);
        SortAndMeasure(algorithm2, arr, n, measureTime, measureComp, count2, time2);
        delete[] arr;

        cout << "Algorithms: " << transferSort(algorithm1) << '|' << transferSort(algorithm2) << endl;
        cout << "Input Size: " << n << endl;
        cout << "Input Order: " << transferMode(param2) << endl;

        cout << "_______________________" << endl;

        if (measureTime) cout << "Running time: " << time1 * 1000 << '|' << time2 * 1000 << " miliseconds" << endl;
        if (measureComp) cout << "Comparisons: " << count1 << '|' << count2 << endl;
 

    }
    else if (argc == 5) {
        // Run both algorithms on given input file
        string inputFileName = param1;

        bool measureTime = true; // Assuming we always measure time in comparison mode
        bool measureComp = true;

        int* arr;
        int n;
        bool fileOpened;
        LoadDataFromFile(inputFileName, arr, n, fileOpened);

        if (!fileOpened) return;

        double time1 = 0.0;
        double time2 = 0.0;
        long long count1 = 0;
        long long count2 = 0;

        // Run sorting algorithms
        SortAndMeasure(algorithm1, arr, n, measureTime, measureComp, count1, time1);
        SortAndMeasure(algorithm2, arr, n, measureTime, measureComp, count2, time2);
        delete[] arr;

        cout << "Algorithms:" << transferSort(algorithm1) << '|' << transferSort(algorithm2) << endl;
        cout << "Input File:" << inputFileName << endl;
        cout << "Input Size:" << n << endl;

        cout << "_______________________" << endl;

        if (measureTime) cout << "Running time:" << time1 * 1000 << '|' << time2 * 1000 << " miliseconds" << endl;
        if (measureComp) cout << "Comparisons:" << count1 << '|' << count2 << endl;

    }
}