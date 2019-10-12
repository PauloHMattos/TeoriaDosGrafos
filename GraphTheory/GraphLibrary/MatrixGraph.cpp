#include "pch.h"
#include "MatrixGraph.h"

void MatrixGraph::AddNode(unsigned int index)
{
	m_Matrix[index] = vector<bool>(m_NodesCount);
}

void MatrixGraph::AddEdge(unsigned int node1, unsigned int node2)
{
	UnweightedGraph::AddEdge(node1, node2);
	m_Matrix[node1 - 1][node2 - 1] = true;
	m_Matrix[node2 - 1][node1 - 1] = true;
}

unsigned int MatrixGraph::GetNeighbor(unsigned int nodeIndex, unsigned int neighborId)
{
	int cnt = neighborId;
	unsigned int i = 0;
	while(cnt >= 0 && i < m_NodesCount)
	{
		if (m_Matrix[nodeIndex - 1][i])
		{
			cnt -= 1;
		}
		i++;
	}
	return i;
}

void MatrixGraph::Resize(unsigned int count)
{
	Graph::Resize(count);
	m_Matrix = vector<vector<bool>>(count);
}