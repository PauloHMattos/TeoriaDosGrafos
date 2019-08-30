#pragma once
#include "Graph.h"
#include <vector>

class GRAPHLIBRARY_API MatrixGraph :
	public Graph
{
public:
	void AddNode(int index) override;
	void AddEdge(int node1, int node2) override;
	forward_list<int> GetNeighbors(int nodeIndex) override;

protected:
	void Resize(unsigned int count) override;

private:
	vector<vector<bool>> m_Matrix;
};