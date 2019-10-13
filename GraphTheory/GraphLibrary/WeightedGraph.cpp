#include "pch.h"
#include "WeightedGraph.h"
#include <queue>
#include <limits>
#include <algorithm>

bool operator > (const Edge& a, const Edge& b) {
	return a.Weight > b.Weight;
}


vector<pair<unsigned int, Edge>> WeightedGraph::MinimumSpanningTree(double* mstWeight, unsigned int startNode)
{
	if (startNode == 0)
	{
		return Kruskal(mstWeight);
	}
	return Prim(mstWeight, startNode);
}

vector<pair<unsigned int, Edge>> WeightedGraph::Prim(double* mstWeight, unsigned int startNode)
{
	auto mst = vector<pair<unsigned int, Edge>>(getNodesCount());

	auto cost = vector<double>(getNodesCount(), numeric_limits<double>::infinity());
	auto inMst = vector<bool>(getNodesCount(), false);

	cost[startNode - 1] = 0;

	priority_queue<Edge, vector<Edge>, greater<Edge>> priorityQueue;
	priorityQueue.push(Edge(startNode, 0));

	unsigned int edgeId = 0;
	while (!priorityQueue.empty())
	{
		unsigned int nodeId = priorityQueue.top().Dest;
		inMst[nodeId - 1] = true;
		priorityQueue.pop();

		for (unsigned int i = 0; i < m_Degrees[nodeId - 1]; i++)
		{
			double weight;
			auto neighborId = GetNeighbor(nodeId, i, &weight);

			if (!inMst[neighborId - 1] && cost[neighborId - 1] > weight)
			{
				auto edge = Edge(neighborId, weight);
				cost[neighborId - 1] = weight;
				priorityQueue.push(edge);
				mst[neighborId - 1] = make_pair(nodeId, edge);
			}
		}
	}

	*mstWeight = 0;
	for (int i = 0; i < getNodesCount(); i++)
	{
		*mstWeight += mst[i].second.Weight;
	}
	return mst;
}

vector<pair<unsigned int, Edge>> WeightedGraph::Kruskal(double* mstWeight)
{
	unsigned int resultId = 0;
	auto mst = vector<pair<unsigned int, Edge>>(getNodesCount());

	auto tempList = vector<vector<Edge>>(m_LinkedList);
	//*
	for (int i = 0; i < tempList.size(); i++)
	{
		sort(tempList[i].begin(), tempList[i].end(), [](const Edge& a, const Edge& b)
		{
			return a.Weight < b.Weight;
		});
	}
	//*/

	Subset* subsets = new Subset[(getNodesCount() * sizeof(Subset))];

	for (unsigned int v = 0; v < getNodesCount(); ++v)
	{
		subsets[v].Parent = v;
		subsets[v].Rank = 0;
	}

	unsigned int nodeId = 1;
	unsigned int edgeId = 0;
	unsigned int offset = 0;
	vector<Edge>* edges = &tempList[nodeId - 1];
	while (resultId < getNodesCount() && edgeId < this->m_EdgesCount)
	{
		if (nodeId >= getNodesCount() - 1)
		{
			int b = 0;
		}

		if (edgeId - offset >= edges->size())
		{
			nodeId++;
			edges = &tempList[nodeId - 1];
			offset = edgeId;
		}

		auto e = (*edges);
		if (e.size() == 0)
		{
			continue;
		}

		auto a = edgeId - offset;
		Edge next_edge = e[a];
		edgeId++;

		int x = Find(subsets, nodeId - 1);
		int y = Find(subsets, next_edge.Dest - 1);

		if (x != y)
		{
			mst[resultId++] = make_pair(nodeId, next_edge);
			Union(subsets, x, y);
			*mstWeight += next_edge.Weight;
		}
	}

	return mst;
}

int WeightedGraph::Find(Subset subsets[], int i)
{
	if (subsets[i].Parent != i)
		subsets[i].Parent = Find(subsets, subsets[i].Parent);

	return subsets[i].Parent;
}

void WeightedGraph::Union(Subset subsets[], int x, int y)
{
	int xroot = Find(subsets, x);
	int yroot = Find(subsets, y);

	if (subsets[xroot].Rank < subsets[yroot].Rank)
		subsets[xroot].Parent = yroot;
	else if (subsets[xroot].Rank > subsets[yroot].Rank)
		subsets[yroot].Parent = xroot;
	else
	{
		subsets[yroot].Parent = xroot;
		subsets[xroot].Rank++;
	}
}

void WeightedGraph::AddNode(unsigned int index)
{
	m_LinkedList.push_back(vector<Edge>());
	//m_LinkedList[index] = (vector<Edge>());
}

void WeightedGraph::AddEdge(unsigned int node1, unsigned int node2, double weight)
{
	Graph::AddEdge(node1, node2);

	m_LinkedList[node1 - 1].push_back(Edge(node2, weight));
	m_LinkedList[node2 - 1].push_back(Edge(node1, weight));
}

double WeightedGraph::Distance(unsigned int startNode, unsigned int endNode, list<unsigned int>* path)
{
	return Dijkstra(startNode, endNode, path);
}

double WeightedGraph::Eccentricity(unsigned int startNode)
{
	double result = 0.0f;
	auto path = list<unsigned int>(); // Não usado

#pragma omp parallel for shared(result)
	for (long i = 1; i < getNodesCount(); i++)
	{
		if (i == startNode)	continue;

		result = max(result, Distance(startNode, i, &path));
	}
	return result;
}

unsigned int WeightedGraph::GetNeighbor(unsigned int nodeIndex, unsigned int neighborId)
{
	double weight;
	return GetNeighbor(nodeIndex, neighborId, &weight);
}

unsigned int WeightedGraph::GetNeighbor(unsigned int nodeIndex, unsigned int neighborId, double* weight)
{
	Edge neighbor = m_LinkedList[nodeIndex - 1][neighborId];
	*weight = neighbor.Weight;
	return neighbor.Dest;
}

void WeightedGraph::Sort()
{
	for (unsigned int i = 0; i < m_NodesCount; i++)
	{
		sort(m_LinkedList[i].begin(), m_LinkedList[i].end(), [](const Edge& a, const Edge& b)
		{
			return a.Dest < b.Dest;
		});
	}
}

void WeightedGraph::Resize(unsigned int count)
{
	Graph::Resize(count);
	m_LinkedList = vector<vector<Edge>>();
	m_LinkedList.reserve(count);
}

void WeightedGraph::LoadEdges(istream& file)
{
	int node1, node2;
	double weight;
	while (file >> node1 >> node2 >> weight)
	{
		AddEdge(node1, node2, weight);
	}
}

double WeightedGraph::Dijkstra(unsigned int startNode, unsigned int endNode, list<unsigned int>* path)
{
	auto distances = vector<double>(getNodesCount(), numeric_limits<double>::infinity());
	distances[startNode  - 1] = 0;

	auto prev = vector<unsigned int>(getNodesCount());

	priority_queue<Edge, vector<Edge>, greater<Edge>> priorityQueue;
	priorityQueue.push(Edge(startNode, 0));

	while (!priorityQueue.empty())
	{
		int nodeId = priorityQueue.top().Dest;

		if (nodeId == endNode)
		{
			break;
		}

		priorityQueue.pop();
		
		for (unsigned int i = 0; i < m_Degrees[nodeId - 1]; i++)
		{
			double weight;
			auto neighborId = GetNeighbor(nodeId, i, &weight);

			if (distances[neighborId - 1] > distances[nodeId - 1] + weight)
			{ 
				distances[neighborId - 1] = distances[nodeId - 1] + weight;
				priorityQueue.push(Edge(neighborId, distances[neighborId - 1]));
				prev[neighborId - 1] = nodeId;
			}
		}
	}

	if (path != nullptr)
	{
		path->clear();
		unsigned int nodeId = endNode;
		while (nodeId != 0)
		{
			path->push_front(nodeId);
			nodeId = prev[nodeId - 1];
		}
	}
	return distances[endNode - 1];
}

