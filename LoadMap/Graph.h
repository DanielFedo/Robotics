/*
 * graph.h
 *
 *  Created on: Apr 14, 2015
 *      Author: colman
 */

#ifndef GRAPH_H_
#define GRAPH_H_

class Graph{

private:
	bool** adjacencyMatrix;
	int** edgeWeightMatrix;
	int vertexCount;

public:
	Graph(int vertexCount);
	~Graph();

	void addEdge(int i, int j, int weight);
	void removeEdge(int i, int j);
	int getEdge(int i, int j);
};




#endif /* GRAPH_H_ */
