#include "pch.h"
#include "UnweightedGraph.h"

void UnweightedGraph::AddEdge(unsigned int node1, unsigned int node2)
{
	Graph::AddEdge(node1, node2);
}


void UnweightedGraph::LoadEdges(istream& file)
{
	int node1, node2;
	while (file >> node1 >> node2)
	{
		AddEdge(node1, node2);
	}
}
