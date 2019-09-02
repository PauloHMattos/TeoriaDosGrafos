#include "pch.h"
#include "MatrixGraph.h"

void MatrixGraph::AddNode(unsigned int index)
{
	m_Matrix[index] = vector<bool>(m_NodesCount);
}

void MatrixGraph::AddEdge(unsigned int node1, unsigned int node2)
{
	Graph::AddEdge(node1, node2);
	m_Matrix[node1 - 1][node2 - 1] = true;
	m_Matrix[node2 - 1][node1 - 1] = true;
}

vector<unsigned int> MatrixGraph::GetNeighbors(unsigned int nodeIndex)
{
	vector<unsigned int> neighbors(m_Degrees[nodeIndex - 1]);
	//*
	for (unsigned int i = 0; i < m_NodesCount; i++)
	{
		if (m_Matrix[nodeIndex - 1][i])
		{
			neighbors.push_back(i + 1);
		}
	}
	//*/
	/*
	for (unsigned int i = m_NodesCount; i >= 1; i--)
	{
		if (m_Matrix[nodeIndex - 1][i - 1])
		{
			neighbors.push_front(i);
		}
	}
	//*/
	return neighbors;
}

void MatrixGraph::Resize(unsigned int count)
{
	Graph::Resize(count);
	m_NodesCount = count;
	m_Matrix = vector<vector<bool>>(count);
}