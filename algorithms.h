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

    void primAlgorithm(int* matrix, int v, int e){
        int* newMatrix = new int[e * (v + 1)];
        int vertex = 0;
        Edge* edges = new Edge[e];
        int edgesSize = 0;
        bool* isUsed = new bool[e];
        for (int i = 0; i < e; i++){
            isUsed[i] = false;
        }

        for(int i = 0; i < v - 1; i++){
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
            if(edges[0].getWeight() > 0 && edges[0].getWeight() < INT_MAX) {
                matrix[i * (v + 1) + v] = edges[0].getWeight();
                matrix[i * (v + 1) + edges[0].getFirstVertex()] = 1;
                matrix[i * (v + 1) + edges[0].getSecondVertex()] = 1;
                vertex = edges[0].getSecondVertex();
            }
        }

        int* oldMatrix = matrix;
        matrix = newMatrix;

        delete[] oldMatrix;
        delete[] edges;
        delete[] isUsed;
    }
}