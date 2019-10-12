#include "pch.h"
#include "ListGraph.h"
#include <algorithm>

void ListGraph::AddNode(unsigned int index)
{
	m_LinkedList.push_back(vector<unsigned int>());
	//m_LinkedList[index] = (vector<unsigned int>());
}

void ListGraph::AddEdge(unsigned int node1, unsigned int node2)
{
	UnweightedGraph::AddEdge(node1, node2);
	m_LinkedList[node1 - 1].push_back(node2);
	m_LinkedList[node2 - 1].push_back(node1);
}

void ListGraph::Sort()
{
//#pragma omp parallel for
	for (unsigned int i = 0; i < m_NodesCount; i++)
	{
		sort(m_LinkedList[i].begin(), m_LinkedList[i].end());
	}
}

unsigned int ListGraph::GetNeighbor(unsigned int nodeIndex, unsigned int neighborId)
{
	return m_LinkedList[nodeIndex - 1][neighborId];
}

void ListGraph::Resize(unsigned int count)
{
	Graph::Resize(count);
	m_LinkedList = vector<vector<unsigned int>>();
	m_LinkedList.reserve(count);
}