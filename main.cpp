#include <ctime>
#include <iostream>
#include "Parameters.h"
#include "fileHandler.h"
#include "List.h"

int N = 1000;

int* convert(std::string* array, int size) {
    int* intArray = new int[size];
    for (int i = 0; i < size; i++){
        intArray[i] = stoi(array[i]);
    }
    return intArray;
}

List* arrayToList(int* array, int size){
    List* list = new List(nullptr, nullptr, 0);
    for (int i = 0; i < size; i++){
        list->addElement(array[i]);
    }
    return list;
}

int* listToArray(List* list, int size){
    int* array = new int[size];
    ListElement* element = list->getFirstElement();
    int i = 0;
    while (element != nullptr && i < size){
        array[i] = element->getValue();
        element = element->getNextElement();
        i++;
    }
    return array;
}

void generateArray(int* array){
    for(int i = 0; i < Parameters::vertexCount; i++){
        for(int j = 0; j < Parameters::vertexCount; j++){
            if(i == j){
                array[i * Parameters::vertexCount + j] = -1;
            }
            else {
                array[i * Parameters::vertexCount + j] = rand();
            }
        }
    }
}

long long runSort(int* array, int N) {
    auto start = std::chrono::high_resolution_clock::now();

    if(array && N){
        std::cout << std::endl;
    }
    switch (Parameters::algorithm) {
        case Parameters::Algorithms::prim:
            std::cout << "Prim algorithm for matrix\n";
            break;
        case Parameters::Algorithms::kruskal:
            std::cout << "Kruskal algorithm for matrix\n";
            break;
        case Parameters::Algorithms::fordFulkerson:
            std::cout << "FordFulkerson algorithm for matrix\n";
            break;
        case Parameters::Algorithms::dijkstra:
            std::cout << "Dijkstra algorithm for matrix\n";
            break;
        case Parameters::Algorithms::bellmanFord:
            std::cout << "BellmanFord algorithm for matrix\n";
            break;
        case Parameters::Algorithms::allAlgorithms:
            std::cout << "All algorithms for matrix\n";
            break;
        default:
            std::cout << "ERROR!!! The algorithm is not supported.";
            return -1;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (Parameters::runMode == Parameters::RunModes::singleFile){
        std::cout << "Time: " << duration.count() << "us\n";
    }

    return duration.count();
}

long long runSortList(List* list, int N) {
    auto start = std::chrono::high_resolution_clock::now();
    if(list && N){
        std::cout << std::endl;
    }
    switch (Parameters::algorithm) {
        case Parameters::Algorithms::prim:
            std::cout << "Prim algorithm for list\n";
            break;
        case Parameters::Algorithms::kruskal:
            std::cout << "Kruskal algorithm for list\n";
            break;
        case Parameters::Algorithms::fordFulkerson:
            std::cout << "FordFulkerson algorithm for list\n";
            break;
        case Parameters::Algorithms::dijkstra:
            std::cout << "Dijkstra algorithm for list\n";
            break;
        case Parameters::Algorithms::bellmanFord:
            std::cout << "BellmanFord algorithm for list\n";
            break;
        case Parameters::Algorithms::allAlgorithms:
            std::cout << "All algorithms for list\n";
            break;
        default:
            std::cout << "ERROR!!! The algorithm is not supported.";
            return -1;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (Parameters::runMode == Parameters::RunModes::singleFile){
        std::cout << "Time: " << duration.count() << "us\n";
    }

    return duration.count();
}

void testMatrix(std::string* fileArray, int N) {
    int* array = convert(fileArray, N);

    runSort(array, N);

    if (Parameters::outputFile != "") {
        fileHandler::saveSorted(array, Parameters::outputFile, N);
    }

    delete[] array;
}

void testList(std::string* fileArray, int N) {
    int* array = convert(fileArray, N);
    List* list = arrayToList(array, N);

    runSortList(list, N);

    if (Parameters::outputFile != "") {
        array = listToArray(list, N);
        fileHandler::saveSorted(array, Parameters::outputFile, N);
    }

    delete list;
    delete[] array;
}

void benchmarkMatrix(Result* results) {
    int* array = new int[Parameters::vertexCount * Parameters::vertexCount];
    generateArray(array);
    for(int i = 0; i < Parameters::iterations; i++){
        long long time = runSort(array, Parameters::vertexCount);
        results[i].setResult(time, Parameters::vertexCount, true);
    }

    if (Parameters::resultsFile != "") {
        fileHandler::writeResults(Parameters::resultsFile, results, Parameters::iterations, Parameters::vertexCount);
    }

    delete[] array;
}

void benchmarkList(Result* results) {
    int* array = new int[Parameters::vertexCount];
    generateArray(array);
    List* list = arrayToList(array, Parameters::vertexCount);

    for(int i = 0; i < Parameters::iterations; i++){
        long long time = runSortList(list, Parameters::vertexCount);
        results[i].setResult(time, Parameters::vertexCount, true);
    }

    if (Parameters::resultsFile != "") {
        fileHandler::writeResults(Parameters::resultsFile, results, Parameters::iterations, Parameters::vertexCount);
    }

    delete list;
    delete[] array;
}

//funkcja uruchamiająca odpowiedni rodzaj testu w zależności od wybranego typu i struktury danych oraz wywołująca odczytanie danych z pliku
void singleFile(){
    if(Parameters::inputFile == ""){
        std::cout << "ERROR!!! No inputFile chosen";
        return;
    }
    std::string* array = fileHandler::readFile(Parameters::inputFile, N);
    if (array == nullptr) {
        return;
    }
    switch (Parameters::structure){
        case Parameters::Structures::incidenceMatrix:
            testMatrix(array, N);
            break;
        case Parameters::Structures::adjacencyList:
            testList(array, N);
            break;
        case Parameters::Structures::allStructures:
            testMatrix(array, N);
            testList(array, N);
            break;
        default:
            std::cout << "ERROR!!! The structure is not supported.";
            return;
    }
    delete[] array;
}

//funkcja uruchamiająca odpowiedni rodzaj benchmarku w zależności od wybranego typu i struktury danych oraz wywołująca wypisanie danych do pliku
void benchmark(){
    if (Parameters::iterations < 1){
        std::cout << "ERROR!!! iteration must be at least 1";
        return;
    }
    if(Parameters::resultsFile == ""){
        std::cout << "ERROR!!! No resultsFile chosen";
        return;
    }
    if(Parameters::vertexCount < 1) {
        std::cout << "ERROR!!! structureSize must be at least 1";
        return;
    }
    Result* results = new Result[Parameters::iterations];
    N = Parameters::vertexCount;
    switch (Parameters::structure){
        case Parameters::Structures::incidenceMatrix:
            benchmarkMatrix(results);
            break;
        case Parameters::Structures::adjacencyList:
            benchmarkList(results);
            break;
        case Parameters::Structures::allStructures:
            benchmarkMatrix(results);
            benchmarkList(results);
            break;
        default:
            std::cout << "ERROR!!! The structure is not supported.";
            return;
    }
    fileHandler::writeResults(Parameters::resultsFile, results, Parameters::iterations, Parameters::vertexCount);
    delete[] results;
}

//funkcja główna programu, w której uruchamiany jest wybrany tryb pracy programu
int main(int argc, char **argv) {
    srand(time(0));
    int paramError = Parameters::readParameters(argc - 1, argv + 1);
    if (paramError != 0) {
      return -1;
    }
    switch (Parameters::runMode){
        case Parameters::RunModes::singleFile:
            singleFile();
            break;
        case Parameters::RunModes::benchmark:
            //benchmark();
            break;
        case Parameters::RunModes::help:
            Parameters::help();
            break;
        default:
            std::cout << "ERROR!!! The runMode is undefined";
            return -1;
    }

    return 0;
}