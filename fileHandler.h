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
    
    std::string* readFile(std::string fileName, int& size);

    void writeResults(std::string fileName, Result* results, int iterations, int structureSize);

    //funkcja zapisująca posortowane dane do pliku
    template<typename T>
    void saveSorted(T* array, std::string fileName, int size){
        deleteFile(fileName);
        std::fstream ftimes;
        std::fstream ferrors;
        ftimes.open(fileName, std::ios::out | std::ios::app);
        //checking if files were found and opened correctly
        if (!ftimes.is_open()) {
            std::cout << "File not found!!!\n";
            return;
        }
        ftimes << size << "\n";
        for (int i = 0; i < size; i++) {
            ftimes << array[i] << "\n";
        }
    }
};