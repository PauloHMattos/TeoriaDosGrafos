#include "pch.h"
#include "ListGraph.h"

void ListGraph::AddNode(unsigned int index)
{
	m_LinkedList.push_back(forward_list<unsigned int>());
}

void ListGraph::AddEdge(unsigned int node1, unsigned int node2)
{
	Graph::AddEdge(node1, node2);
	m_LinkedList[node1 - 1].push_front(node2);
	m_LinkedList[node2 - 1].push_front(node1);
}

void ListGraph::Sort()
{
	for (int i = 0; i < m_NodesCount; i++)
	{
		m_LinkedList[i].sort();
	}
}

forward_list<unsigned int> ListGraph::GetNeighbors(unsigned int nodeIndex)
{
	return m_LinkedList[nodeIndex - 1];
}

void ListGraph::Resize(unsigned int count)
{
	Graph::Resize(count);
	m_NodesCount = count;
	m_LinkedList.reserve(count);
}