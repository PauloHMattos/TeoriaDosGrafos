#pragma once
#include "Graph.h"
#include <vector>

class DLL_EXPORT_OR_IMPORT MatrixGraph :
	public Graph
{
public:
	void AddNode(unsigned int index) override;
	void AddEdge(unsigned int node1, unsigned int node2) override;
	unsigned int GetNeighbor(unsigned int nodeIndex, unsigned int neighborId) override;

protected:
	void Resize(unsigned int count) override;

private:
	vector<vector<bool>> m_Matrix;
};