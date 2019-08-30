#include "pch.h"
#include "Graph.h"

#include <fstream>


bool Graph::Load(string path)
{
	ifstream file;
	file.open("C:\\Users\\Paulo\\Documents\\GitHub\\TeoriaDosGrafos\\GraphTheory\\x64\\Debug\\as_graph.txt");
	//file.open(path);

	if (!file.good())
	{
		return false;
	}

	unsigned int nodesCount;
	file >> nodesCount;
	Resize(nodesCount);

	nodesCount = 0;
	while (nodesCount < getNodesCount())
	{
		AddNode(nodesCount);
		nodesCount++;
	}

	int node1, node2;
	while (file >> node1 >> node2)
	{
		AddEdge(node1, node2);
	}
	return true;
}

void Graph::AddEdge(int node1, int node2)
{
	m_EdgesCount++;
}