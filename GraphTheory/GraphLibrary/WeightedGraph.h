#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#pragma once

#include "Graph.h"

struct Edge
{
	unsigned int Dest;
	double Weight;

	Edge()
	{
		Dest = 0;
		Weight = 0;
	}

	Edge(unsigned int nodeId, double weight)
	{
		Dest = nodeId;
		Weight = weight;
	}
};


class DLL_EXPORT_OR_IMPORT WeightedGraph :
	public Graph
{
public:
	void AddNode(unsigned int index) override;
	void AddEdge(unsigned int node1, unsigned int node2, double weight);
	double Distance(unsigned int startNode, unsigned int endNode, list<unsigned int>* path);
	vector<pair<unsigned int, Edge>> MinimumSpanningTree(double* mstWeight, unsigned int startNode = 1);
	double Eccentricity(unsigned int startNode);

	unsigned int GetNeighbor(unsigned int nodeIndex, unsigned int neighborId) override;
	unsigned int GetNeighbor(unsigned int nodeIndex, unsigned int neighborId, double*weight);

protected:
	void Sort() override;
	void Resize(unsigned int count) override;
	void LoadEdges(istream& file) override;
	vector<double> Dijkstra(unsigned int startNode, unsigned int endNode, list<unsigned int>* path);
	vector<pair<unsigned int, Edge>> Prim(double* mstWeight, unsigned int startNode);
	vector<pair<unsigned int, Edge>> Kruskal(double* mstWeight);

private:
	vector<vector<Edge>> m_LinkedList;

	class Subset
	{
	public:
		unsigned int Parent;
		int Rank;
	};

	int Find(Subset subsets[], int i);
	void Union(Subset subsets[], int x, int y);
};

#endif