#include "Edge.h"
#include "List.h"

namespace algorithms {

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

    void primAlgorithm(int*& matrix, int* mst, int v, int e){
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
        
        for(int i = 0; i < v - 1; i++){
            for (int j = 0; j < v + 1; j++){
                std::cout << mst[i * (v + 1) + j] << ", ";
            }
            std::cout << std::endl;
        }

        delete[] edges;
        delete[] isUsed;
        delete[] isVisited;
    }
}