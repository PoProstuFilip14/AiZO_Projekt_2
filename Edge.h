#pragma once

class Edge
{
	protected:
		int weight = -1;
		int firstVertex = -1;
		int secondVertex = -1;
	public:
		Edge(int weight = -1, int firstVertex = -1, int secondVertex = -1);

		void setEdge(int weight, int firstVertex, int secondVertex);

		int getWeight();

		void setWeight(int weight);

		int getFirstVertex();

		int getSecondVertex();
};