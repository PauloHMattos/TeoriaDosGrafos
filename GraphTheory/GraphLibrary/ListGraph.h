#pragma once
#include "Graph.h"
#include <vector>
#include <forward_list>

using namespace std;

class GRAPHLIBRARY_API ListGraph :
	public Graph
{
public:
	void AddNode(int index) override;
	void AddEdge(int node1, int node2) override;


protected:
	void Resize(unsigned int count) override;

private:
	vector<forward_list<int>> m_LinkedList;
};

