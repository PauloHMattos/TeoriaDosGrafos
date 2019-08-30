#pragma once
#include "Graph.h"
#include <vector>
#include <forward_list>

class GRAPHLIBRARY_API ListGraph :
	public Graph
{
public:
	void AddNode(int index) override;
	void AddEdge(int node1, int node2) override;
	void Sort() override;

	forward_list<int> GetNeighbors(int nodeIndex) override;

protected:
	void Resize(unsigned int count) override;

private:
	vector<forward_list<int>> m_LinkedList;
};

