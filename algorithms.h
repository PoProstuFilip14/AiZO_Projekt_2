#include "Edge.h"
#include "List.h"
#include <climits>

namespace algorithms {
    int defaultSize = -1;
    int defaultLength = -1;

    //implementacja sortowania przez wstawianie dla tablicy
    template <typename T>
    void insertionSort(T* array, int size) {
        for (int i = size - 2; i >= 0; i--) {
            for (int j = i; j < size - 1; j++) {
                if (array[j].getWeight() > array[j + 1].getWeight()) {
                    T helper = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = helper;
                }
                else {
                    break;
                }
            }
        }
    }

    void primAlgorithm(int* matrix, int* mst, int v, int e){
        for(int i = 0; i < v - 1; i++){
            for(int j = 0; j < v + 1; j++){
                mst[i * (v + 1) + j] = -1;
            }
        }
        int vertex = 0;
        Edge* edges = new Edge[e];
        int edgesSize = 0;
        bool* isUsed = new bool[e];
        bool* isVisited = new bool[v];
        for (int i = 0; i < e; i++){
            isUsed[i] = false;
        }
        for (int i = 0; i < v; i++){
            isVisited[i] = false;
        }

        for(int i = 0; i < v - 1; i++){
            isVisited[vertex] = true;
            for(int j = 0; j < e; j++){
                if(matrix[j * (v + 1) + vertex] == 1 && isUsed[j] == false){
                    int secondVertex = -1;
                    for(int k = 0; k < v; k++){
                        if(k != vertex && matrix[j * (v + 1) + k] == 1) secondVertex = k;
                    }
                    edges[edgesSize].setEdge(matrix[j * (v + 1) + v], vertex, secondVertex);
                    isUsed[j] = true;
                    edgesSize++;
                }
            }
            insertionSort(edges, edgesSize);
            for(int j = 0; j < edgesSize; j++){
                if(edges[j].getWeight() > 0 && edges[j].getWeight() < INT_MAX && !isVisited[edges[j].getSecondVertex()]) {
                    mst[i * (v + 1) + v] = edges[j].getWeight();
                    mst[i * (v + 1) + edges[j].getFirstVertex()] = 1;
                    mst[i * (v + 1) + edges[j].getSecondVertex()] = 1;
                    vertex = edges[j].getSecondVertex();
                    edges[j].setWeight(INT_MAX);
                    break;
                }
            }
        }

        delete[] edges;
        delete[] isUsed;
        delete[] isVisited;
    }

    void primAlgorithm(List<List<std::pair<int, int>>*>* list, List<List<std::pair<int, int>>*>* mst, int v, int e){
        
        for(int i = 0; i < v; i++){
            mst->addElementDouble(new List<std::pair<int, int>>(nullptr, nullptr, 0));
        }
        int vertex = 0;
        Edge* edges = new Edge[e];
        int edgesSize = 0;
        bool* isUsed = new bool[e];
        bool* isVisited = new bool[v];
        for (int i = 0; i < v; i++){
            isVisited[i] = false;
        }
        for(int i = 0; i < v - 1; i++){
            isVisited[vertex] = true;
            ListElement<std::pair<int, int>>* currentElement = list->getElementDouble(vertex)->getFirstElement();
            while(currentElement != nullptr){
                if(!isVisited[currentElement->getValue().first]){
                    edges[edgesSize].setEdge(currentElement->getValue().second, vertex, currentElement->getValue().first);
                    edgesSize++;
                }
                currentElement = currentElement->getNextElement();
            }
            insertionSort(edges, edgesSize);
            for(int j = 0; j < edgesSize; j++){
                if(edges[j].getWeight() > 0 && edges[j].getWeight() < INT_MAX && !isVisited[edges[j].getSecondVertex()]) {
                    mst->getElementDouble(edges[j].getFirstVertex())->addElementDouble({edges[j].getSecondVertex(), edges[j].getWeight()});
                    vertex = edges[j].getSecondVertex();
                    edges[j].setWeight(INT_MAX);
                    break;
                }
            }
            delete currentElement;
        }

        delete[] edges;
        delete[] isUsed;
        delete[] isVisited;
    }

    void dijkstraAlgorithm(int* matrix, int* &shortestPath, int v, int e, int start, int finish, int& numberOfEdges, int& length) {
        bool* isVisited = new bool[v];
        int* d = new int[v];
        int* p = new int[v];
        int currentVertex = start;

        for (int i = 0; i < v; i++) {
            isVisited[i] = false;
            d[i] = INT_MAX;
            p[i] = -1;
        }
        d[currentVertex] = 0;

        for (int i = 0; i < v; i++) {
            isVisited[currentVertex] = true;

            for (int j = 0; j < e; j++) {
                if(matrix[j * (v + 1) + currentVertex] > 0){
                    for (int k = 0; k < v; k++){
                        if(matrix[j * (v + 1) + k] < 0 && d[k] > d[currentVertex] + matrix[j * (v + 1) + v]){
                            d[k] = d[currentVertex] + matrix[j * (v + 1) + v];
                            p[k] = currentVertex;
                        }
                    }
                }
            }

            int shortestVertex = INT_MAX;
            int newVertex = -1;
            for(int i = 0; i < v; i++){
                if(!isVisited[i] && shortestVertex > d[i]){
                    shortestVertex = d[i];
                    newVertex = i;
                }
            }

            if(newVertex != -1){
                currentVertex = newVertex;
            }
        }

        int size = 1;
        int* initialPath = new int[v];
        currentVertex = finish;
        initialPath[0] = finish;
        while(currentVertex != start){
            currentVertex = p[currentVertex];
            initialPath[size] = currentVertex;
            size++;
        }

        shortestPath = new int[size];
        for(int i = 0; i < size; i++){
            shortestPath[size - i - 1] = initialPath[i];
        }

        numberOfEdges = size;
        length = d[finish];
        
        delete[] isVisited;
        delete[] p;
        delete[] d;
        delete[] initialPath;
    }

    void dijkstraAlgorithm(List<List<std::pair<int, int>>*>* list, List<int>* &shortestPath, int v, int start, int finish, int& numberOfEdges, int& length) {
        bool* isVisited = new bool[v];
        int* d = new int[v];
        int* p = new int[v];
        int currentVertex = start;

        for (int i = 0; i < v; i++) {
            isVisited[i] = false;
            d[i] = INT_MAX;
            p[i] = -1;
        }
        d[currentVertex] = 0;

        /*for (int i = 0; i < v; i++){
            ListElement<std::pair<int, int>>* currentVertex = list->getElementDouble(i)->getFirstElement();
            std::cout << i << " ";
            while(currentVertex != nullptr){
                std::cout << currentVertex->getValue().first << " ";
                currentVertex = currentVertex->getNextElement();
            }
            std::cout << std::endl;
        }*/

        for (int i = 0; i < v; i++) {
            isVisited[currentVertex] = true;

            ListElement<std::pair<int, int>>* currentElement = list->getElementDouble(currentVertex)->getFirstElement();
            while(currentElement != nullptr){
                if(d[currentElement->getValue().first] > d[currentVertex] + currentElement->getValue().second){
                    d[currentElement->getValue().first] = d[currentVertex] + currentElement->getValue().second;
                    p[currentElement->getValue().first] = currentVertex;
                }
                currentElement = currentElement->getNextElement();
            }

            int shortestVertex = INT_MAX;
            int newVertex = -1;
            for(int i = 0; i < v; i++){
                if(!isVisited[i] && shortestVertex > d[i]){
                    shortestVertex = d[i];
                    newVertex = i;
                }
            }

            if(newVertex != -1){
                currentVertex = newVertex;
            }
        }

        int size = 1;
        int* initialPath = new int[v];
        currentVertex = finish;
        initialPath[0] = finish;
        while(currentVertex != start){
            currentVertex = p[currentVertex];
            initialPath[size] = currentVertex;
            size++;
        }

        for(int i = 0; i < size; i++){
            shortestPath->addElement(initialPath[size - i - 1]);
        }

        numberOfEdges = size;
        length = d[finish];
        
        delete[] isVisited;
        delete[] p;
        delete[] d;
        delete[] initialPath;
    }
}