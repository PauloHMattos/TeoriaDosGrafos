#include "pch.h"
#include "MatrixGraph.h"

void MatrixGraph::AddNode(unsigned int index)
{
	vector<bool> line = vector<bool>(m_NodesCount);
	m_Matrix[index] = line;
}

void MatrixGraph::AddEdge(unsigned int node1, unsigned int node2)
{
	Graph::AddEdge(node1, node2);
	m_Matrix[node1 - 1][node2 - 1] = true;
	m_Matrix[node2 - 1][node1 - 1] = true;
}

forward_list<unsigned int> MatrixGraph::GetNeighbors(unsigned int nodeIndex)
{
	forward_list<unsigned int> neighbors;
	
	for (int i = m_NodesCount - 1; i >= 0; i--)
	{
		if (m_Matrix[nodeIndex - 1][i])
		{
			neighbors.push_front(i + 1);
		}
	}

	return neighbors;
}

void MatrixGraph::Resize(unsigned int count)
{
	Graph::Resize(count);
	m_NodesCount = count;
	m_Matrix = vector<vector<bool>>(count);
}