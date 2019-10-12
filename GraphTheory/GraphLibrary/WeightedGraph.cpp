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
	auto mst = vector<pair<unsigned int, Edge>>(getNodesCount() - 1);

	float inf = numeric_limits<float>::infinity();
	auto cost = vector<float>(getNodesCount(), inf);
	auto inMST = vector<bool>(getNodesCount(), false);

	cost[startNode] = 0;
	*mstWeight = 0;

	priority_queue<Edge, vector<Edge>, greater<Edge>> priorityQueue;
	priorityQueue.push(Edge(startNode, 0));

	unsigned int edgeId = 0;
	while (!priorityQueue.empty())
	{
		int nodeId = priorityQueue.top().Dest;

		inMST[nodeId] = true;
		priorityQueue.pop();

		for (unsigned int i = 0; i < m_Degrees[nodeId - 1]; i++)
		{
			float weight;
			auto neighborId = GetNeighbor(nodeId, i, &weight);

			if (!inMST[neighborId] && cost[neighborId] > weight)
			{
				// Updating key of v 

				auto edge = Edge(neighborId, weight);
				cost[neighborId] = weight;
				priorityQueue.push(edge);
				mst[edgeId] = make_pair(nodeId, edge);
				*mstWeight += edge.Weight;
			}
		}
	}
	return mst;
}

vector<pair<unsigned int, Edge>> WeightedGraph::Kruskal(float* mstWeight, unsigned int startNode)
{
	auto mst = vector<pair<unsigned int, Edge>>(getNodesCount());

	auto tempList = vector<vector<Edge>>(m_LinkedList);
	for (int i = 0; i < tempList.size(); i++)
	{
		sort(tempList[i].begin(), tempList[i].end());
	}

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

		// Step 2: Pick the smallest edge. And increment  
		// the index for next iteration  
		Edge next_edge = (*edges)[edgeId];

		int x = Find(subsets, nodeId);
		int y = Find(subsets, next_edge.Dest);

		// If including this edge does't cause cycle,  
		// include it in result and increment the index  
		// of result for next edge  
		if (x != y)
		{
			mst[edgeId++] = make_pair(nodeId, next_edge);
			Union(subsets, x, y);
			*mstWeight += next_edge.Weight;
		}
		// Else discard the next_edge  
	}

	return mst;
}

void WeightedGraph::AddEdge(unsigned int node1, unsigned int node2, float weight)
{
	Graph::AddEdge(node1, node2);

	m_LinkedList[node1 - 1].push_back(Edge(node2, weight));
	m_LinkedList[node2 - 1].push_back(Edge(node1, weight));
}

float WeightedGraph::Distance(unsigned int startNode, unsigned int endNode, list<unsigned int> path)
{
	return Dijkstra(startNode, endNode, path);
}

float WeightedGraph::Eccentricity(unsigned int startNode)
{
	float result = 0.0f;

#pragma omp parallel for shared(result)
	for (long i = 0; i < getNodesCount(); i++)
	{
		if (i == startNode)	continue;

		auto path = list<unsigned int>(); // Não usado
		result = max(result, Distance(startNode, i, path));
	}
	return result;
}

unsigned int WeightedGraph::GetNeighbor(unsigned int nodeIndex, unsigned int neighborId, float* weight)
{
	Edge neighbor = m_LinkedList[nodeIndex - 1][neighborId];
	*weight = neighbor.Weight;
	return neighbor.Dest;
}

float WeightedGraph::Dijkstra(unsigned int startNode, unsigned int endNode, list<unsigned int> path)
{
	float minDistance = numeric_limits<float>::infinity();
	auto distances = vector<float>(getNodesCount(), minDistance);
	distances[startNode] = 0;

	priority_queue<Edge, vector<Edge>, greater<Edge>> priorityQueue;
	priorityQueue.push(Edge(startNode, 0));

	while (!priorityQueue.empty())
	{
		int nodeId = priorityQueue.top().Dest;
		minDistance += priorityQueue.top().Weight;
		path.push_back(nodeId);

		priorityQueue.pop();
		
		for (unsigned int i = 0; i < m_Degrees[nodeId - 1]; i++)
		{
			float weight;
			auto neighborId = GetNeighbor(nodeId, i, &weight);

			if (distances[neighborId] > distances[nodeId] + weight)
			{ 
				distances[neighborId] = distances[nodeId] + weight;
				priorityQueue.push(Edge(neighborId, distances[neighborId]));
			}
		}
	}

	return minDistance;
}

