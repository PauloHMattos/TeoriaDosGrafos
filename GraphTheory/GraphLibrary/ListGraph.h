#pragma once
#include "UnweightedGraph.h"
#include <vector>
#include <forward_list>

class DLL_EXPORT_OR_IMPORT ListGraph :
	public UnweightedGraph
{
public:
	void AddNode(unsigned int index) override;
	void AddEdge(unsigned int node1, unsigned int node2) override;
	void Sort() override;

	unsigned int GetNeighbor(unsigned int nodeIndex, unsigned int neighborId) override;

protected:
	void Resize(unsigned int count) override;

private:
	vector<vector<unsigned int>> m_LinkedList;
};

