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

List<int>* arrayToList(int* array, int size){
    List<int>* list = new List<int>(nullptr, nullptr, 0);
    for (int i = 0; i < size; i++){
        list->addElement(array[i]);
    }
    return list;
}

int* listToArray(List<int>* list, int size){
    int* array = new int[size];
    ListElement<int>* element = list->getFirstElement();
    int i = 0;
    while (element != nullptr && i < size){
        array[i] = element->getValue();
        element = element->getNextElement();
        i++;
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

long long runSort(int* array, int* mst, int V, int E) {
    auto start = std::chrono::high_resolution_clock::now();

    if(array && V){
        std::cout << std::endl;
    }
    switch (Parameters::algorithm) {
        case Parameters::Algorithms::prim:
            algorithms::primAlgorithm(array, mst, V, E);
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
        
    for(int i = 0; i < V - 1; i++){
        for (int j = 0; j < V + 1; j++){
            std::cout << mst[i * (V + 1) + j] << ", ";
        }
        std::cout << std::endl;
    }

    return duration.count();
}

long long runSortList(List<int>* list, int V) {
    auto start = std::chrono::high_resolution_clock::now();
    if(list && V){
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

void testMatrix(int* array, int* mst, int V, int E) {

    runSort(array, mst, V, E);
        
    for(int i = 0; i < V - 1; i++){
        for (int j = 0; j < V + 1; j++){
            std::cout << mst[i * (V + 1) + j] << ", ";
        }
        std::cout << std::endl;
    }

    if (Parameters::outputFile != "") {
        fileHandler::saveSorted(mst, Parameters::outputFile, V, V - 1);
    }
}

void testList(int* array, int V) {
    List<int>* list = arrayToList(array, V);

    runSortList(list, V);

    if (Parameters::outputFile != "") {
        array = listToArray(list, V);
        fileHandler::saveSorted(array, Parameters::outputFile, V, E);
    }

    delete list;
    delete[] array;
}

void benchmarkMatrix(Result* results) {
    int edgesCount = ((Parameters::vertexCount * (Parameters::vertexCount - 1)) / 2) * Parameters::density / 100;
    int* array = new int[Parameters::vertexCount * Parameters::vertexCount];
    int* mst = new int[(V - 1) * (V + 1)];
    for(int i = 0; i < Parameters::iterations; i++){
        generateArray(array, edgesCount);
        int* matrix = arrayToMatrix(array, edgesCount);
        long long time = runSort(matrix, mst, Parameters::vertexCount, edgesCount);
        results[i].setResult(time, Parameters::vertexCount, true);
        delete[] matrix;
    }

    if (Parameters::resultsFile != "") {
        fileHandler::writeResults(Parameters::resultsFile, results, Parameters::iterations, Parameters::vertexCount);
    }

    delete[] array;
    delete[] mst;
}

void benchmarkList(Result* results) {
    int* array = new int[Parameters::vertexCount];
    //generateArray(array);
    List<int>* list = arrayToList(array, Parameters::vertexCount);

    for(int i = 0; i < Parameters::iterations; i++){
        long long time = runSortList(list, Parameters::vertexCount);
        results[i].setResult(time, Parameters::vertexCount, true);
    }

    if (Parameters::resultsFile != "") {
        fileHandler::writeResults(Parameters::resultsFile, results, Parameters::iterations, Parameters::vertexCount);
    }

    delete list;
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
    int* mst = new int[(V - 1) * (V + 1)];
    switch (Parameters::structure){
        case Parameters::Structures::incidenceMatrix:
            testMatrix(array, mst, V, E);
            break;
        case Parameters::Structures::adjacencyList:
            testList(array, V);
            break;
        case Parameters::Structures::allStructures:
            testMatrix(array, mst, V, E);
            testList(array, V);
            break;
        default:
            std::cout << "ERROR!!! The structure is not supported.";
            return;
    }
    delete[] array;
    delete[] mst;
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