#include <ctime>
#include <iostream>
#include <climits>
#include "Parameters.h"
#include "fileHandler.h"
#include "List.h"
#include "algorithms.h"

int V = 1000;
int E = 1000;
int defaultSize = -1;
int defaultLength = -1;

int* convert(std::string* array, int size) {
    int* intArray = new int[size];
    for (int i = 0; i < size; i++){
        intArray[i] = stoi(array[i]);
    }
    return intArray;
}

List<List<std::pair<int, int>>*>* arrayToList(int* array, int v, int e){
    if(!(Parameters::problem == Parameters::Problems::mst) && Parameters::runMode == Parameters::RunModes::benchmark) e *= 2;
    List<List<std::pair<int, int>>*>* list = new List<List<std::pair<int, int>>*>(nullptr, nullptr, 0);
    for(int i = 0; i < v; i++){
        list->addElement(new List<std::pair<int, int>>(nullptr, nullptr, 0));
    }
    for (int i = 0; i < e; i++){
        int firstVertex = -1;
        int secondVertex = -1;
        if(Parameters::problem == Parameters::Problems::mst){
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
        else{
            for(int j = 0; j < v; j++){
                if (array[i * (v + 1) + j] == 1){
                    firstVertex = j;
                }
                if (array[i * (v + 1) + j] == -1){
                    secondVertex = j;
                }
            }
            int weigth = array[i * (v + 1) + v];
            list->getElementDouble(firstVertex)->addElement({secondVertex, weigth});
        }
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

int* listToArray(List<int>* list, int size){
    int* array = new int[size];
    ListElement<int>* currentElement = list->getFirstElement();
    for(int i = 0; i < size; i++){
        if(currentElement == nullptr){
            size = i;
            break;
        }
        array[i] = currentElement->getValue();
        currentElement = currentElement->getNextElement();
    }
    return array;
}

int* arrayToMatrix(int* array, int e){
    if(!(Parameters::problem == Parameters::Problems::mst)) e *= 2;
    int* matrix = new int[e * (Parameters::vertexCount + 1)];
    int edgeCount = 0;
    for(int i = 0; i < Parameters::vertexCount; i++){
        int limit = i;
        if(!(Parameters::problem == Parameters::Problems::mst)) limit = Parameters::vertexCount;
        for (int j = 0; j < limit; j++){
            if(array[i * Parameters::vertexCount + j] > 0){
                for(int k = 0; k < Parameters::vertexCount; k++){
                    if (Parameters::problem == Parameters::Problems::mst){
                        if(k == i || k == j){
                            matrix[edgeCount * (Parameters::vertexCount + 1) + k] = 1;
                        }
                        else{
                            matrix[edgeCount * (Parameters::vertexCount + 1) + k] = -1;
                        }
                    }
                    else{
                        if(k == i){
                            matrix[edgeCount * (Parameters::vertexCount + 1) + k] = 1;
                        }
                        else if (k == j){
                            matrix[edgeCount * (Parameters::vertexCount + 1) + k] = -1;
                        }
                        else{
                            matrix[edgeCount * (Parameters::vertexCount + 1) + k] = 0;
                        }
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
    int minimalEdges = 0;
    int maximalEdges = INT_MAX;
    if(Parameters::problem == Parameters::Problems::mst){
        minimalEdges = Parameters::vertexCount - 1;
        maximalEdges = (Parameters::vertexCount * (Parameters::vertexCount - 1)) / 2;
    }
    else{
        minimalEdges = (Parameters::vertexCount - 1) * 2;
        maximalEdges = Parameters::vertexCount * (Parameters::vertexCount - 1);
        edgesCount *= 2;
    }
    if(Parameters::density < 50){
        for(int i = 0; i < Parameters::vertexCount; i++){
            for(int j = 0; j < i; j++){
                if (j == i + 1 || i == j + 1){
                    array[i * Parameters::vertexCount + j] = rand() + 1;
                    if(Parameters::problem == Parameters::Problems::mst){
                        array[j * Parameters::vertexCount + i] = array[i * Parameters::vertexCount + j];
                    }
                    else{
                        array[j * Parameters::vertexCount + i] = rand() + 1;
                    }
                }
                else {
                    array[i * Parameters::vertexCount + j] = -1;
                    array[j * Parameters::vertexCount + i] = -1;
                }
            }
        }
        for(int i = minimalEdges; i < edgesCount; i++) {
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
            if (Parameters::problem == Parameters::Problems::mst){
                array[secondVertex * Parameters::vertexCount + firstVertex] = array[firstVertex * Parameters::vertexCount + secondVertex];
            }
        }
    }
    else{
        for(int i = 0; i < Parameters::vertexCount; i++){
            array[i * Parameters::vertexCount + i] = -1;
            for (int j = 0; j < i; j++){
                array[i * Parameters::vertexCount + j] = rand() + 1;
                if(Parameters::problem == Parameters::Problems::mst){
                    array[j * Parameters::vertexCount + i] = array[i * Parameters::vertexCount + j];
                }
                else{
                    array[j * Parameters::vertexCount + i] = rand() + 1;
                }
            }
        }
        for(int i = maximalEdges; i > edgesCount; i--) {
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
            if (Parameters::problem == Parameters::Problems::mst){
                array[secondVertex * Parameters::vertexCount + firstVertex] = -1;
            }
        }
    }
}

long long runSort(int* array, int*& result, int v, int e, int start = -1, int finish = -1, int& size = defaultSize, int& length = defaultLength) {
    auto startTime = std::chrono::high_resolution_clock::now();

    switch (Parameters::algorithm) {
        case Parameters::Algorithms::prim:
            if (Parameters::problem == Parameters::Problems::mst){
                result = new int[(v - 1) * (v + 1)];
                algorithms::primAlgorithm(array, result, v, e);
            }
            else{
                std::cout << "Wrong problem-algorithm combination\n";
            }
            break;
        case Parameters::Algorithms::kruskal:
            std::cout << "Kruskal algorithm for matrix is not supported\n";
            break;
        case Parameters::Algorithms::fordFulkerson:
            std::cout << "FordFulkerson algorithm for matrix is not supported\n";
            break;
        case Parameters::Algorithms::dijkstra:
            if (Parameters::problem == Parameters::Problems::sp){
                if (start < 0 || finish < 0){
                    std::cout << "Start or finish are not valid\n";
                    break;
                }
                algorithms::dijkstraAlgorithm(array, result, v, e, start, finish, size, length);
            }
            else{
                std::cout << "Wrong problem-algorithm combination\n";
            }
            break;
        case Parameters::Algorithms::bellmanFord:
            std::cout << "BellmanFord algorithm for matrix is not supported\n";
            break;
        case Parameters::Algorithms::allAlgorithms:
            if (Parameters::problem == Parameters::Problems::sp){
                if (start < 0 || finish < 0){
                    std::cout << "Start or finish are not valid\n";
                    break;
                }
                algorithms::dijkstraAlgorithm(array, result, v, e, start, finish, size, length);
            }
            if (Parameters::problem == Parameters::Problems::mst){
                result = new int[(v - 1) * (v + 1)];
                algorithms::primAlgorithm(array, result, v, e);
            }
            else{
                std::cout << "Problem is not supported\n";
            }
            break;
        default:
            std::cout << "ERROR!!! The algorithm is not supported.";
            return -1;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - startTime);

    if (Parameters::runMode == Parameters::RunModes::singleFile){
        std::cout << "Time: " << duration.count() << "us\n";
    }

    return duration.count();
}

long long runSortList(List<List<std::pair<int, int>>*>* list, List<List<std::pair<int, int>>*>* result = nullptr, List<int>* resultPath = nullptr, int v = -1, int e = -1, int start = -1, int finish = -1, int& size = defaultSize, int& length = defaultLength) {
    auto startTime = std::chrono::high_resolution_clock::now();

    switch (Parameters::algorithm) {
        case Parameters::Algorithms::prim:
            if (Parameters::problem == Parameters::Problems::mst){
                algorithms::primAlgorithm(list, result, v, e);
            }
            else{
                std::cout << "Wrong problem-algorithm combination\n";
            }
            break;
            
        case Parameters::Algorithms::kruskal:
            std::cout << "Kruskal algorithm for list is not supported\n";
            break;
        case Parameters::Algorithms::fordFulkerson:
            std::cout << "FordFulkerson algorithm for list is not supported\n";
            break;
        case Parameters::Algorithms::dijkstra:
            if (Parameters::problem == Parameters::Problems::sp){
                if (start < 0 || finish < 0){
                    std::cout << "Start or finish are not valid\n";
                    break;
                }
                algorithms::dijkstraAlgorithm(list, resultPath, v, start, finish, size, length);
            }
            else{
                std::cout << "Wrong problem-algorithm combination\n";
            }
            break;
        case Parameters::Algorithms::bellmanFord:
            std::cout << "BellmanFord algorithm for list is not supported\n";
            break;
        case Parameters::Algorithms::allAlgorithms:
            if (Parameters::problem == Parameters::Problems::sp){
                if (start < 0 || finish < 0){
                    std::cout << "Start or finish are not valid\n";
                    break;
                }
                algorithms::dijkstraAlgorithm(list, resultPath, v, start, finish, size, length);
            }
            if (Parameters::problem == Parameters::Problems::mst){
                algorithms::primAlgorithm(list, result, v, e);
            }
            else{
                std::cout << "Problem is not supported\n";
            }
            break;
        default:
            std::cout << "ERROR!!! The algorithm is not supported.";
            return -1;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - startTime);

    if (Parameters::runMode == Parameters::RunModes::singleFile){
        std::cout << "Time: " << duration.count() << "us\n";
    }

    return duration.count();
}

void testMatrix(int* array, int v, int e) {
    int* result = nullptr;
    int size = -1;
    int length = -1;

    if(Parameters::problem == Parameters::Problems::mst){
        runSort(array, result, v, e);
        if (Parameters::outputFile != "" && result != nullptr) {
            fileHandler::saveSorted(result, Parameters::outputFile, v, v - 1);
        }
    }
    else{
        runSort(array, result, v, e, Parameters::vertexStart, Parameters::vertexEnd, size, length);
        if (Parameters::outputFile != "" && result != nullptr) {
            fileHandler::saveSortedPath(result, Parameters::outputFile, size, length);
        }
    }

    if(result != nullptr) delete[] result;
}

void testList(int* array, int v, int e) {
    List<List<std::pair<int, int>>*>* list = arrayToList(array, v, e);
    List<List<std::pair<int, int>>*>* result = new List<List<std::pair<int, int>>*>(nullptr, nullptr, 0);
    List<int>* resultPath = new List<int>(nullptr, nullptr, 0);
    int size = -1;
    int length = -1;

    if(Parameters::problem == Parameters::Problems::mst){
        runSortList(list, result, nullptr, v, e);
        if (Parameters::outputFile != "" && result->getFirstElement() != nullptr) {
            int* matrix = listToArray(result, v);
            fileHandler::saveSorted(matrix, Parameters::outputFile, v, v - 1);
            delete[] matrix;
        }
    }
    else{
        runSortList(list, nullptr, resultPath, v, e, Parameters::vertexStart, Parameters::vertexEnd, size, length);
        if (Parameters::outputFile != "" && resultPath->getFirstElement() != nullptr) {
            int* matrix = listToArray(resultPath, size);
            fileHandler::saveSortedPath(matrix, Parameters::outputFile, size, length);
            delete[] matrix;
        }
    }

    delete list;
    delete result;
    delete resultPath;
}

void benchmarkMatrix(Result* results) {
    int edgesCount = ((Parameters::vertexCount * (Parameters::vertexCount - 1)) / 2) * Parameters::density / 100;
    int* array = new int[Parameters::vertexCount * Parameters::vertexCount];
    int* result = new int[(V - 1) * (V + 1)];
    int size = -1;
    int length = -1;
    for(int i = 0; i < Parameters::iterations; i++){
        generateArray(array, edgesCount);
        int* matrix = arrayToMatrix(array, edgesCount);
        long long time = 0;
        if(Parameters::problem == Parameters::Problems::mst){
            time = runSort(matrix, result, Parameters::vertexCount, edgesCount);
        }
        else{
            int start = rand() % Parameters::vertexCount;
            int finish = rand() % Parameters::vertexCount;
            while(start == finish){
                finish = rand() % Parameters::vertexCount;
            }
            time = runSort(matrix, result, Parameters::vertexCount, edgesCount * 2, start, finish, size, length);
        }
        results[i].setResult(time, Parameters::vertexCount);
        delete[] matrix;
    }

    if (Parameters::resultsFile != "") {
        fileHandler::writeResults(Parameters::resultsFile, results, Parameters::iterations, Parameters::vertexCount);
    }

    delete[] array;
    delete[] result;
}

void benchmarkList(Result* results) {
    int* array = new int[Parameters::vertexCount * Parameters::vertexCount];
    int size = -1;
    int length = -1;

    for(int i = 0; i < Parameters::iterations; i++){
        int edgesCount = ((Parameters::vertexCount * (Parameters::vertexCount - 1)) / 2) * Parameters::density / 100;
        generateArray(array, edgesCount);
        int* matrix = arrayToMatrix(array, edgesCount);
        /*for(int i = 0; i < edgesCount * 2; i++){
            for(int j = 0; j < (Parameters::vertexCount + 1); j++){
                std::cout << matrix[i * (Parameters::vertexCount + 1) + j] << " "; 
            }
            std::cout << std::endl;
        }*/
        List<List<std::pair<int, int>>*>* list = arrayToList(matrix, Parameters::vertexCount, edgesCount);
        List<List<std::pair<int, int>>*>* mst = new List<List<std::pair<int, int>>*>(nullptr, nullptr, 0);
        List<int>* resultPath = new List<int>(nullptr, nullptr, 0);
        long long time;
        if(Parameters::problem == Parameters::Problems::mst){
            time = runSortList(list, mst, nullptr, Parameters::vertexCount, edgesCount);
        }
        else{
            int start = rand() % Parameters::vertexCount;
            int finish = rand() % Parameters::vertexCount;
            while(start == finish){
                finish = rand() % Parameters::vertexCount;
            }
            time = runSortList(list, nullptr, resultPath, Parameters::vertexCount, edgesCount * 2, start, finish, size, length);
        }
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
    int* array = nullptr;
    if(Parameters::problem == Parameters::Problems::mst){
        array = fileHandler::readFile(Parameters::inputFile, V, E, false);
    }
    else{
        array = fileHandler::readFile(Parameters::inputFile, V, E, true);
    }
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

void help(){
    std::cout << "Options:\n";
    std::cout << "\n";
    std::cout << "Run modes (mutually exclusive):\n";
    std::cout << "  -f, --singleFile   Test a single file\n";
    std::cout << "  -b, --benchmark    Benchmark test (random values every iteration)\n";
    std::cout << "  -h, --help         Show help message\n";
    std::cout << "\n";
    std::cout << "Common options: \n";
    std::cout << "  -p, --problem VAL     0 - Minimum spanning tree\n";
    std::cout << "                        1 - Shortest path\n";
    std::cout << "  -a, --algorithm VAL   0 - Run all algorithms available for given problem\n";
    std::cout << "                        1 - Prim's algorithm\n";
    std::cout << "                        3 - Dijkstra's algorithm\n";
    std::cout << "  -s, --structure VAL   0 - Run for all structures\n";
    std::cout << "                        1 - Incidence matrix\n";
    std::cout << "                        2 - Adjacency list\n";
    std::cout << "\n";
    std::cout << "Single file options:\n";
    std::cout << "  -i, --inputFile FILE     File with graph\n";
    std::cout << "  -o, --outputFile FILE    Save here graph structure and solution/solutions for given parameters (there is no defined way to do it, as long as you print everything it will be fine)\n";
    std::cout << "  -c, --vertexStart VAL    Current/starting vertex (SP/MF problems)\n";
    std::cout << "  -e, --vertexEnd VAL      End vertex (SP/MF problems)\n";
    std::cout << "\n";
    std::cout << "Benchmark options:\n";
    std::cout << "  -r, --resultsFile FILE   Results (time and parameters) will be saved to this file\n";
    std::cout << "  -l, --vertexCount VAL    How many vertices in the generated graph\n";
    std::cout << "  -d, --density VAL        Density of generated graph as ineger (e.g. 25%)\n";
    std::cout << "  -n, --iterations ITE :)  How many repetitions of the research with the given parameters\n";
    std::cout << "\n";
    std::cout << "Examples:\n";
    std::cout << "  ./project --singleFile --inputFile \"in.txt\" --outputFile \"out.txt\" -p 1 -a 3 -s 1 -c 2 -e 5\n";
    std::cout << "  Load graph from file \"in.txt\" and load it into the incidence matrix. Using Prim's algorithm solve the shortest path problem from vertex 2 to vertex 5. Save solution to the \"out.txt\".\n";
    std::cout << "  ./project --benchmark -p 0 -a 0 -s 0 -l 35 -d 75 -n 50 -r \"res.txt\"\n";
    std::cout << "  Repeat following test 50 times: Generate a graph with 35 vertices and 75% density. Solve MST problem for that graph using every implemented algorithm, and every implemented structure seperately. Results save in \"res.txt\"\n";
    std::cout << "\n";
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
            help();
            break;
        default:
            std::cout << "ERROR!!! The runMode is undefined";
            return -1;
    }

    return 0;
}