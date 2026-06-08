#include <ctime>
#include <iostream>
#include "Parameters.h"
#include "fileHandler.h"
#include "List.h"
#include "algorithms.h"

int V = 1000;
int E = 1000;

int* convert(std::string* array, int size) {
    int* intArray = new int[size];
    for (int i = 0; i < size; i++){
        intArray[i] = stoi(array[i]);
    }
    return intArray;
}

List<List<std::pair<int, int>>*>* arrayToList(int* array, int v, int e){
    List<List<std::pair<int, int>>*>* list = new List<List<std::pair<int, int>>*>(nullptr, nullptr, 0);
    for(int i = 0; i < v; i++){
        list->addElement(new List<std::pair<int, int>>(nullptr, nullptr, 0));
    }
    for (int i = 0; i < e; i++){
        int firstVertex = -1;
        int secondVertex = -1;
        int vertexCounter = 0;
        for(int j = 0; j < v; j++){
            if (array[i * (v + 1) + j] == 1){
                if(vertexCounter == 0) firstVertex = j;
                else secondVertex = j;
                vertexCounter++;
            }
        }
        int weigth = array[i * (v + 1) + v];
        list->getElementDouble(firstVertex)->addElement({secondVertex, weigth});
        list->getElementDouble(secondVertex)->addElement({firstVertex, weigth});
    }
    return list;
}

int* listToArray(List<List<std::pair<int, int>>*>* list, int v){
    int* array = new int[(v - 1) * (v + 1)];
    for(int i = 0; i < v - 1; i++){
        for (int j = 0; j < v + 1; j++){
            array[i * (v + 1) + j] = -1;
        }
    }
    int vertex = 0;
    int i = 0;
    ListElement<List<std::pair<int, int>>*>* currentList = list->getFirstElement();
    while(currentList != nullptr){
        ListElement<std::pair<int, int>>* currentElement = list->getElementDouble(vertex)->getFirstElement();
        while(currentElement != nullptr){
            array[i * (v + 1) + v] = currentElement->getValue().second;
            array[i * (v + 1) + vertex] = 1;
            array[i * (v + 1) + currentElement->getValue().first] = 1;
            i++;
            currentElement = currentElement->getNextElement();
        }
        currentList = currentList->getNextElement();
        vertex++;
    }
    return array;
}

int* arrayToMatrix(int* array, int e){
    int* matrix = new int[e * (Parameters::vertexCount + 1)];
    int edgeCount = 0;
    for(int i = 0; i < Parameters::vertexCount; i++){
        for (int j = 0; j < i; j++){
            if(array[i * Parameters::vertexCount + j] > 0){
                for(int k = 0; k < Parameters::vertexCount; k++){
                    if(k == i || k == j){
                        matrix[edgeCount * (Parameters::vertexCount + 1) + k] = 1;
                    }
                    else{
                        matrix[edgeCount * (Parameters::vertexCount + 1) + k] = -1;
                    }
                }
                matrix[edgeCount * (Parameters::vertexCount + 1) + Parameters::vertexCount] = array[i * Parameters::vertexCount + j];
                edgeCount++;
            }
        }
    }
    return matrix;
}

void generateArray(int* array, int edgesCount){
    if(Parameters::density < 50){
        for(int i = 0; i < Parameters::vertexCount; i++){
            for(int j = 0; j < i; j++){
                if (j == i + 1 || i == j + 1){
                    array[i * Parameters::vertexCount + j] = rand() + 1;
                    array[j * Parameters::vertexCount + i] = array[i * Parameters::vertexCount + j];
                }
                else {
                    array[i * Parameters::vertexCount + j] = -1;
                    array[j * Parameters::vertexCount + i] = -1;
                }
            }
        }
        for(int i = Parameters::vertexCount - 1; i < edgesCount; i++) {
            int firstVertex = -1;
            int secondVertex = -1;
            do{
                firstVertex = rand() % Parameters::vertexCount;
                secondVertex = rand() % Parameters::vertexCount;
                while (firstVertex == secondVertex){
                    secondVertex = rand() % Parameters::vertexCount;
                }
            } while(array[firstVertex * Parameters::vertexCount + secondVertex] != -1);
            array[firstVertex * Parameters::vertexCount + secondVertex] = rand() + 1;
            array[secondVertex * Parameters::vertexCount + firstVertex] = array[firstVertex * Parameters::vertexCount + secondVertex];
        }
    }
    else{
        for(int i = 0; i < Parameters::vertexCount; i++){
            array[i * Parameters::vertexCount + i] = -1;
            for (int j = 0; j < i; j++){
                array[i * Parameters::vertexCount + j] = rand() + 1;
                array[j * Parameters::vertexCount + i] = array[i * Parameters::vertexCount + j];
            }
        }
        for(int i = (Parameters::vertexCount * (Parameters::vertexCount - 1)) / 2; i > edgesCount; i--) {
            int firstVertex = -1;
            int secondVertex = -1;
            do{
                firstVertex = rand() % Parameters::vertexCount;
                secondVertex = rand() % Parameters::vertexCount;
                while (firstVertex == secondVertex || firstVertex == secondVertex + 1 || secondVertex == firstVertex + 1){
                    secondVertex = rand() % Parameters::vertexCount;
                }
            } while(array[firstVertex * Parameters::vertexCount + secondVertex] == -1);
            array[firstVertex * Parameters::vertexCount + secondVertex] = -1;
            array[secondVertex * Parameters::vertexCount + firstVertex] = -1;
        }
    }
}

long long runSort(int* array, int* mst, int v, int e) {
    auto start = std::chrono::high_resolution_clock::now();

    if(array && v){
        std::cout << std::endl;
    }
    switch (Parameters::algorithm) {
        case Parameters::Algorithms::prim:
            algorithms::primAlgorithm(array, mst, v, e);
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

long long runSortList(List<List<std::pair<int, int>>*>* list, List<List<std::pair<int, int>>*>* mst, int v, int e) {
    auto start = std::chrono::high_resolution_clock::now();
    if(list && v){
        std::cout << std::endl;
    }
    switch (Parameters::algorithm) {
        case Parameters::Algorithms::prim:
            algorithms::primAlgorithm(list, mst, v, e);
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

void testMatrix(int* array, int v, int e) {
    int* mst = new int[(v - 1) * (v + 1)];

    runSort(array, mst, v, e);

    if (Parameters::outputFile != "") {
        fileHandler::saveSorted(mst, Parameters::outputFile, v, v - 1);
    }

    delete[] mst;
}

void testList(int* array, int v, int e) {
    List<List<std::pair<int, int>>*>* list = arrayToList(array, v, e);
    List<List<std::pair<int, int>>*>* mst = new List<List<std::pair<int, int>>*>(nullptr, nullptr, 0);;

    runSortList(list, mst, v, e);

    if (Parameters::outputFile != "") {
        int* matrix = listToArray(mst, v);
        fileHandler::saveSorted(matrix, Parameters::outputFile, v, v - 1);
        delete[] matrix;
    }

    delete list;
    delete mst;
}

void benchmarkMatrix(Result* results) {
    int edgesCount = ((Parameters::vertexCount * (Parameters::vertexCount - 1)) / 2) * Parameters::density / 100;
    int* array = new int[Parameters::vertexCount * Parameters::vertexCount];
    int* mst = new int[(V - 1) * (V + 1)];
    for(int i = 0; i < Parameters::iterations; i++){
        generateArray(array, edgesCount);
        int* matrix = arrayToMatrix(array, edgesCount);
        long long time = runSort(matrix, mst, Parameters::vertexCount, edgesCount);
        results[i].setResult(time, Parameters::vertexCount);
        delete[] matrix;
    }

    if (Parameters::resultsFile != "") {
        fileHandler::writeResults(Parameters::resultsFile, results, Parameters::iterations, Parameters::vertexCount);
    }

    delete[] array;
    delete[] mst;
}

void benchmarkList(Result* results) {
    int* array = new int[Parameters::vertexCount * Parameters::vertexCount];

    for(int i = 0; i < Parameters::iterations; i++){
        int edgesCount = ((Parameters::vertexCount * (Parameters::vertexCount - 1)) / 2) * Parameters::density / 100;
        generateArray(array, edgesCount);
        int* matrix = arrayToMatrix(array, edgesCount);
        List<List<std::pair<int, int>>*>* list = arrayToList(matrix, Parameters::vertexCount, edgesCount);
        List<List<std::pair<int, int>>*>* mst = new List<List<std::pair<int, int>>*>(nullptr, nullptr, 0);
        long long time = runSortList(list, mst, Parameters::vertexCount, edgesCount);
        results[i].setResult(time, Parameters::vertexCount);

        delete list;
        delete mst;
        delete[] matrix;
    }

    if (Parameters::resultsFile != "") {
        fileHandler::writeResults(Parameters::resultsFile, results, Parameters::iterations, Parameters::vertexCount);
    }
}

//funkcja uruchamiająca odpowiedni rodzaj testu w zależności od wybranego typu i struktury danych oraz wywołująca odczytanie danych z pliku
void singleFile(){
    if(Parameters::inputFile == ""){
        std::cout << "ERROR!!! No inputFile chosen";
        return;
    }
    int* array = fileHandler::readFile(Parameters::inputFile, V, E);
    if (array == nullptr) {
        return;
    }
    switch (Parameters::structure){
        case Parameters::Structures::incidenceMatrix:
            testMatrix(array, V, E);
            break;
        case Parameters::Structures::adjacencyList:
            testList(array, V, E);
            break;
        case Parameters::Structures::allStructures:
            testMatrix(array, V, E);
            testList(array, V, E);
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
    if (Parameters::density <= 0 || Parameters::density > 100){
        std::cout << "ERROR!!! density must be greater than 0 and not greater than 100";
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
    V = Parameters::vertexCount;
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
            benchmark();
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