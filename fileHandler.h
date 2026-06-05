#pragma once
#include "Result.h"
#include <string>
#include <fstream>
#include <iostream>

namespace fileHandler{
    double getAverageTime(Result* results, int iterations);

    double getErrorPercentage(Result* results, int iterations);

    int getMax(Result* results, int iterations);

    int getMin(Result* results, int iterations);

    void deleteFile(std::string fileName);
    
    int* readFile(std::string fileName, int& v, int& e);

    void writeResults(std::string fileName, Result* results, int iterations, int structureSize);

    void saveSorted(int* matrix, std::string fileName, int v, int e);
};