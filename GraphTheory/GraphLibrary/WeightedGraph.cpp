#include "pch.h"
#include "WeightedGraph.h"
#include <queue>
#include <limits>

vector<pair<unsigned int, Edge>> WeightedGraph::MinimumSpanningTree(float* mstWeight, unsigned int startNode)
{
	return Prim(mstWeight, startNode);
}

vector<pair<unsigned int, Edge>> WeightedGraph::Prim(float* mstWeight, unsigned int startNode)
{
	auto mst = vector<pair<unsigned int, Edge>>(getNodesCount());

	float inf = numeric_limits<float>::infinity();
	auto cost = vector<float>(getNodesCount(), inf);
	auto inMST = vector<bool>(getNodesCount(), false);

	cost[startNode - 1] = 0;
	*mstWeight = 0;

	priority_queue<Edge, vector<Edge>, greater<Edge>> priorityQueue;
	priorityQueue.push(Edge(startNode, 0));

	unsigned int edgeId = 0;
	while (!priorityQueue.empty())
	{
		int nodeId = priorityQueue.top().Dest;

		inMST[nodeId - 1] = true;
		priorityQueue.pop();

		for (unsigned int i = 0; i < m_Degrees[nodeId - 1]; i++)
		{
			float weight;
			auto neighborId = GetNeighbor(nodeId, i, &weight);

			if (!inMST[neighborId - 1] && cost[neighborId - 1] > weight)
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

vector<pair<unsigned int, Edge>> WeightedGraph::Kruskal(float* mstWeight, unsigned int startNode)
{
	auto mst = vector<pair<unsigned int, Edge>>();
	mst.reserve(getNodesCount());

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

	unsigned int nodeId = 0;
	unsigned int edgeId = 0;
	vector<Edge>* edges = &tempList[nodeId];
	while (mst.size() < getNodesCount() - 1 && edgeId < this->m_EdgesCount)
	{
		if (++edgeId >= edges->size())
		{
			nodeId++;
			edges = &tempList[nodeId];
		}

		Edge next_edge = (*edges)[edgeId];

		int x = Find(subsets, nodeId);
		int y = Find(subsets, next_edge.Dest);

		if (x != y)
		{
			mst[edgeId++] = make_pair(nodeId, next_edge);
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

void WeightedGraph::AddEdge(unsigned int node1, unsigned int node2, float weight)
{
	Graph::AddEdge(node1, node2);

	m_LinkedList[node1 - 1].push_back(Edge(node2, weight));
	m_LinkedList[node2 - 1].push_back(Edge(node1, weight));
}

float WeightedGraph::Distance(unsigned int startNode, unsigned int endNode, list<unsigned int>& path)
{
	return Dijkstra(startNode, endNode, path);
}

float WeightedGraph::Eccentricity(unsigned int startNode)
{
	float result = 0.0f;

#pragma omp parallel for shared(result)
	for (long i = 1; i < getNodesCount(); i++)
	{
		if (i == startNode)	continue;

		auto path = list<unsigned int>(); // Não usado
		result = max(result, Distance(startNode, i, path));
	}
	return result;
}

unsigned int WeightedGraph::GetNeighbor(unsigned int nodeIndex, unsigned int neighborId)
{
	float weight;
	return GetNeighbor(nodeIndex, neighborId, &weight);
}

unsigned int WeightedGraph::GetNeighbor(unsigned int nodeIndex, unsigned int neighborId, float* weight)
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
	float weight;
	while (file >> node1 >> node2 >> weight)
	{
		AddEdge(node1, node2, weight);
	}
}

float WeightedGraph::Dijkstra(unsigned int startNode, unsigned int endNode, list<unsigned int>& path)
{
	auto distances = vector<float>(getNodesCount(), numeric_limits<float>::infinity());
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
			float weight;
			auto neighborId = GetNeighbor(nodeId, i, &weight);

			if (distances[neighborId - 1] > distances[nodeId - 1] + weight)
			{ 
				distances[neighborId - 1] = distances[nodeId - 1] + weight;
				priorityQueue.push(Edge(neighborId, distances[neighborId - 1]));
				prev[neighborId - 1] = nodeId;
			}
		}
	}

	path.clear();
	unsigned int nodeId = endNode;
	while (nodeId != 0)
	{
		path.push_front(nodeId);
		nodeId = prev[nodeId - 1];
	}
	return distances[endNode - 1];
}

