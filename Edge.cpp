#include "Edge.h"

Edge::Edge(int weight, int firstVertex, int secondVertex){
    this->firstVertex = firstVertex;
    this->secondVertex = secondVertex;
    this->weight = weight;
}

void Edge::setEdge(int weight, int firstVertex, int secondVertex){
    this->firstVertex = firstVertex;
    this->secondVertex = secondVertex;
    this->weight = weight;
}

int Edge::getWeight(){
    return weight;
}

int Edge::getFirstVertex(){
    return firstVertex;
}

int Edge::getSecondVertex(){
    return secondVertex;
}