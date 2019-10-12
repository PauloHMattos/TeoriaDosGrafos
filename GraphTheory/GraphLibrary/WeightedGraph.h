#pragma once

#include "Graph.h"
//#include <tuple>

struct Edge
{
	unsigned int Dest;
	float Weight;

	Edge::Edge(unsigned int nodeId, float weight)
	{
		Dest = nodeId;
		Weight = weight;
	}
};

bool operator > (const Edge& a, const Edge& b) {
	return a.Weight > b.Weight;
}


class WeightedGraph :
	public Graph
{
public:
	void AddEdge(unsigned int node1, unsigned int node2, float weight);
	float Distance(unsigned int startNode, unsigned int endNode, list<unsigned int> path);
	vector<pair<unsigned int, Edge>> MinimumSpanningTree(float* mstWeight, unsigned int startNode = 1);
	float Eccentricity(unsigned int startNode);

	unsigned int GetNeighbor(unsigned int nodeIndex, unsigned int neighborId, float *weight);

protected:
	float Dijkstra(unsigned int startNode, unsigned int endNode, list<unsigned int> path);
	vector<pair<unsigned int, Edge>> Prim(float* mstWeight, unsigned int startNode);
	vector<pair<unsigned int, Edge>> Kruskal(float* mstWeight, unsigned int startNode);

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

