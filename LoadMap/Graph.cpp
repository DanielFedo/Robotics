/*
 * Graph.c
 *
 *  Created on: Apr 14, 2015
 *      Author: colman
 */

#include "Graph.h"

Graph::Graph(int vertexCount)
{
	this->vertexCount = vertexCount;
	adjacencyMatrix = new bool*[vertexCount];
	edgeWeightMatrix = new int*[vertexCount];

	// Give default values for the edges
	for (int i = 0; i < vertexCount; i++)
	{
		adjacencyMatrix[i] = new bool[vertexCount];
		edgeWeightMatrix[i] = new int[vertexCount];
		for (int j = 0; j < vertexCount; j++)
		{
			adjacencyMatrix[i][j] = false;
			edgeWeightMatrix[i][j] = -1;
		}
	}
}

void Graph::addEdge(int i, int j, int weight)
{
	if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount)
	{
		// Create the edges
		adjacencyMatrix[i][j] = true;
		adjacencyMatrix[j][i] = true;

		// Give the edges weight
		edgeWeightMatrix[i][j] = 1;
		edgeWeightMatrix[j][i] = 1;
	}
}

void Graph::removeEdge(int i, int j)
{
	if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount)
	{
		// Create the edges
		adjacencyMatrix[i][j] = false;
		adjacencyMatrix[j][i] = false;

		// Give the edges weight
		edgeWeightMatrix[i][j] = -1;
		edgeWeightMatrix[j][i] = -1;
	}
}

// Return the value of the edge if it exists. If it doesn't exist, returns -1.
int Graph::getEdge(int i, int j)
{
	int edgeWeight = -1;

	if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount)
	{
		// If edge exist
		if (adjacencyMatrix[i][j])
		{
			edgeWeight = edgeWeightMatrix[i][j];
		}
	}

	return edgeWeight;
}
