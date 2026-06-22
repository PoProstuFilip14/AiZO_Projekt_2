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
            average += results[i].getTime();
            count++;
        }

        if (count == 0) return 0;

        return (double)average / count;
    }

    //znajdywanie maksymalnej wartości dla serii pomiarowej
    int getMax(Result* results, int iterations){
        long long max = -1;
        for(int i = 0; i < iterations; i++){
            if(results[i].getTime() > max){
                max = results[i].getTime();
            }
        }

        return max;
    }

    //znajdywanie maksymalnej wartości dla serii pomiarowej
    int getMin(Result* results, int iterations){
        long long min = std::numeric_limits<long long>::max();
        for(int i = 0; i < iterations; i++){
            if(results[i].getTime() < min){
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
    int* readFile(std::string fileName, int& v, int& e, bool isAsymmetric) {
        std::ifstream ff(fileName);

        if (!ff) {
            std::cout << "ERROR!!! No such file" << std::endl;
            return nullptr;
        }

        ff >> v >> e;

        int* matrix = new int[e * (v + 1)];
        for (int i = 0; i < e; i++) {
            for (int j = 0; j < v + 1; j++) {
                if(!isAsymmetric){
                    matrix[i * (v + 1) + j] = -1;
                }
                else{
                    matrix[i * (v + 1) + j] = 0;
                }
            }
        }

        int firstVertex, secondVertex, weight;

        for (int i = 0; i < e; i++) {
            ff >> firstVertex >> secondVertex >> weight;

            matrix[i * (v + 1) + v] = weight;
            matrix[i * (v + 1) + firstVertex] = 1;
            if(!isAsymmetric){
                matrix[i * (v + 1) + secondVertex] = 1;
            }
            else{
                matrix[i * (v + 1) + secondVertex] = -1;
            }
        }

        ff.close();

        return matrix;
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
        ftimes << "\n";
        
        ftimes << "Lp,";
        ftimes << "Rozmiar,";
        ftimes << "Czas,";
        ftimes << "Data,";
        ftimes << "\n";
        for (int i = 0; i < iterations; i++) {
            std::time_t t = results[i].getTimestamp();
            std::tm* tm = std::localtime(&t);

            ftimes << i + 1 << ",";
            ftimes << structureSize << ",";
            ftimes << results[i].getTime() << ",";
            ftimes << std::put_time(tm, "%Y-%m-%d %H:%M:%S") << ",";
            ftimes << "\n";
        }
        ftimes.close();
    }
    
    //funkcja zapisująca posortowane dane do pliku
    void saveSorted(int* matrix, std::string fileName, int v, int e){
        std::fstream ftimes;
        std::fstream ferrors;
        ftimes.open(fileName, std::ios::out | std::ios::app);
        //checking if files were found and opened correctly
        if (!ftimes.is_open()) {
            std::cout << "File not found!!!\n";
            return;
        }
        ftimes << v << "    " << e << "\n";
        for (int i = 0; i < e; i++) {
            int firstVertex = -1;
            int secondVertex = -1;
            int vertexCounter = 0;
            for(int j = 0; j < v; j++){
                if (matrix[i * (v + 1) + j] == 1){
                    if(vertexCounter == 0) firstVertex = j;
                    else secondVertex = j;
                    vertexCounter++;
                }
            }
            int weigth = matrix[i * (v + 1) + v];
            ftimes << firstVertex << "  " << secondVertex << "  " << weigth << "\n";
        }
    }

    void saveSortedPath(int* result, std::string fileName, int size, int length){
        std::fstream ftimes;
        std::fstream ferrors;
        ftimes.open(fileName, std::ios::out | std::ios::app);
        //checking if files were found and opened correctly
        if (!ftimes.is_open()) {
            std::cout << "File not found!!!\n";
            return;
        }
        ftimes << size << "    " << length << "\n";
        for (int i = 0; i < size; i++) {
            ftimes << result[i] << "\n";
        }
    };
};