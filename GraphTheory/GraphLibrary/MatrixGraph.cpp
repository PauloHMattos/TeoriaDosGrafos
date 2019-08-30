#include "pch.h"
#include "MatrixGraph.h"

void MatrixGraph::AddNode(int index)
{
	vector<bool> line = vector<bool>(m_NodesCount);
	m_Matrix[index] = line;
}

void MatrixGraph::AddEdge(int node1, int node2)
{
	if (node1 > m_NodesCount || node2 > m_NodesCount)
	{
		return;
	}
	Graph::AddEdge(node1, node2);

	m_Matrix[node1 - 1][node2 - 1] = 1;
	m_Matrix[node2 - 1][node1 - 1] = 1;
}

forward_list<int> MatrixGraph::GetNeighbors(int nodeIndex)
{
	forward_list<int> neighbors;
	
	for (int i = 0; i < m_NodesCount; i++)
	{
		if (m_Matrix[nodeIndex][i])
		{
			neighbors.push_front(i);
		}
	}

	return neighbors;
}

void MatrixGraph::Resize(unsigned int count)
{
	m_NodesCount = count;
	m_Matrix = vector<vector<bool>>(count);
	//m_Matrix.reserve(count);
}