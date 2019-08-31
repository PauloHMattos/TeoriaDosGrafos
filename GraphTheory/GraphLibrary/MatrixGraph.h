#pragma once
#include "Graph.h"
#include <vector>

class GRAPHLIBRARY_API MatrixGraph :
	public Graph
{
public:
	void AddNode(unsigned int index) override;
	void AddEdge(unsigned int node1, unsigned int node2) override;
	forward_list<unsigned int> GetNeighbors(unsigned int nodeIndex) override;

protected:
	void Resize(unsigned int count) override;

private:
	vector<vector<bool>> m_Matrix;
};