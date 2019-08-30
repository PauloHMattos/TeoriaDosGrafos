#include "pch.h"
#include "ListGraph.h"
#include <execution>
#include <ppl.h>

using namespace concurrency;

void ListGraph::AddNode(int index)
{
	m_LinkedList.push_back(forward_list<int>());
}

void ListGraph::AddEdge(int node1, int node2)
{
	if (node1 > m_NodesCount || node2 > m_NodesCount)
	{
		return;
	}
	Graph::AddEdge(node1, node2);
	m_LinkedList[node1 - 1].push_front(node2);
	m_LinkedList[node2 - 1].push_front(node1);
}

void ListGraph::Sort()
{
	/*
	parallel_for(unsigned int(0), m_NodesCount, [&](int i)
	{
		forward_list<int> list = m_LinkedList[i];
		list.sort();
	});
	//*/
	/*
	std::for_each(std::execution::par_unseq, m_LinkedList.begin(), m_LinkedList.end(), [&](int i)
	{
		m_LinkedList[i].sort();
	});
	//*/
	//*
#pragma omp parallel for
	for (int i = 0; i < m_NodesCount; i++)
	{
		m_LinkedList[i].sort();
	}
	//*/

	/*
	for (int i = 0; i < m_NodesCount; i++)
	{
		forward_list<int> list = m_LinkedList[i];
		sort(std::execution::par_unseq, list.begin(), list.end());
	}
	//*/


}

forward_list<int> ListGraph::GetNeighbors(int nodeIndex)
{
	return m_LinkedList[nodeIndex - 1];
}

void ListGraph::Resize(unsigned int count)
{
	m_NodesCount = count;
	m_LinkedList.reserve(count);
}