#pragma once
#include "Graph.h"
#include <vector>
#include <forward_list>

class GRAPHLIBRARY_API ListGraph :
	public Graph
{
public:
	void AddNode(unsigned int index) override;
	void AddEdge(unsigned int node1, unsigned int node2) override;
	void Sort() override;

	forward_list<unsigned int> GetNeighbors(unsigned int nodeIndex) override;

protected:
	void Resize(unsigned int count) override;

private:
	vector<forward_list<unsigned int>> m_LinkedList;
};

