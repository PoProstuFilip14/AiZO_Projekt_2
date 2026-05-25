#include "fileHandler.h"
#include "Result.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <iomanip>

namespace fileHandler{
    //obliczanie średniego czasu dla serii pomiarowej
    double getAverageTime(Result* results, int iterations){
        long long average = 0;
        int count = 0;
        for(int i = 0; i < iterations; i++){
            if(results[i].getError()){
                average += results[i].getTime();
                count++;
            }
        }

        if (count == 0) return 0;

        return (double)average / count;
    }

    //oblicznie procentu błędnych wyników dla serii pomiarowej
    double getErrorPercentage(Result* results, int iterations){
        int count = 0;

        for(int i = 0; i < iterations; i++){
            if(results[i].getError()){
                count++;
            }
        }

        return 100 - ((double)count / iterations * 100);
    }

    //znajdywanie maksymalnej wartości dla serii pomiarowej
    int getMax(Result* results, int iterations){
        long long max = -1;
        for(int i = 0; i < iterations; i++){
            if(results[i].getTime() > max && results[i].getError()){
                max = results[i].getTime();
            }
        }

        return max;
    }

    //znajdywanie maksymalnej wartości dla serii pomiarowej
    int getMin(Result* results, int iterations){
        long long min = std::numeric_limits<long long>::max();
        for(int i = 0; i < iterations; i++){
            if(results[i].getTime() < min && results[i].getError()){
                min = results[i].getTime();
            }
        }

        return min;
    }

    //funkcja, która usuwa dane z pliku
    void deleteFile(std::string fileName) {
        remove(fileName.c_str());
    }
            
    //funkcja czytająca dane wejściowe z pliku
    std::string* readFile(std::string fileName, int& size) {
        std::ifstream ff(fileName);

        if (!ff) {
            std::cout << "ERROR!!! No such file" << std::endl;
            return nullptr;
        }

        ff >> size;

        std::string* tab = new std::string[size];

        for (int i = 0; i < size; i++) {
            ff >> tab[i];
        }

        ff.close();

        return tab;
    }

    //funkcja zapisująca wyniki pomiarów do pliku
    void writeResults(std::string fileName, Result* results, int iterations, int structureSize) {
        deleteFile("./results/" + fileName + ".csv");
        std::fstream ftimes;
        std::fstream ferrors;
        ftimes.open("./results/" + fileName + ".csv", std::ios::out | std::ios::app);
        if (!ftimes.is_open()) {
            std::cout << "ERROR!!! File not found!!!\n";
            return;
        }
        ftimes << std::fixed << std::setprecision(0);
        
        ftimes << "Rozmiar,";
        ftimes << "Sredni_Czas,";
        ftimes << "Max,";
        ftimes << "Min,";
        ftimes << "Procent_Bledow,";
        ftimes << "\n";

        ftimes << structureSize << ",";
        ftimes << fileHandler::getAverageTime(results, iterations) << ",";
        ftimes << fileHandler::getMax(results, iterations) << ",";
        ftimes << fileHandler::getMin(results, iterations) << ",";
        ftimes << fileHandler::getErrorPercentage(results, iterations) << ",";
        ftimes << "\n";
        
        ftimes << "Lp,";
        ftimes << "Rozmiar,";
        ftimes << "Czas,";
        ftimes << "Data,";
        ftimes << "Blad,";
        ftimes << "\n";
        for (int i = 0; i < iterations; i++) {
            std::time_t t = results[i].getTimestamp();
            std::tm* tm = std::localtime(&t);

            ftimes << i + 1 << ",";
            ftimes << structureSize << ",";
            ftimes << results[i].getTime() << ",";
            ftimes << std::put_time(tm, "%Y-%m-%d %H:%M:%S") << ",";
            ftimes << results[i].getError() << ",";
            ftimes << "\n";
        }
        ftimes.close();
    };
};