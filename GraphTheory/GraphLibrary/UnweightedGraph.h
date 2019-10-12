#pragma once
#include "Graph.h"

class DLL_EXPORT_OR_IMPORT UnweightedGraph : public Graph
{
public:
	virtual void AddEdge(unsigned int node1, unsigned int node2);


protected:
	void LoadEdges(istream& file) override;

};

