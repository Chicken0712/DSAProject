#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

//void GenerateAndWriteRandomData(const string&, int);
//void GenerateAndWriteNearlySortedData(const string&, int);
//void GenerateAndWriteSortedData(const string&, int);
//void GenerateAndWriteReverseData(const string&, int);
void writeData(const string&, int*, int);
void LoadDataFromFile(const string&, int*&, int&, bool&);
void SortAndMeasure(const string&, int[], int, bool, bool,long long&, double&);
void GenerateAndMeasureForAll(const string&, int, const string&);
string transferSort(string);

