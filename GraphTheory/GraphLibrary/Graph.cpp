#include "pch.h"
#include "Graph.h"

#include <fstream>
#include <queue>
#include <stack>
#include <iostream>
#include <climits>

bool Graph::Load(string path)
{
	INIT_TIMER;
	START_TIMER;
	ifstream file;
	file.open(path);

	if (!file.good())
	{
		return false;
	}

	unsigned int nodesCount;
	file >> nodesCount;
	Resize(nodesCount);

	nodesCount = 0;
	while (nodesCount < getNodesCount())
	{
		AddNode(nodesCount);
		nodesCount++;
	}

	int node1, node2;
	while (file >> node1 >> node2)
	{
		AddEdge(node1, node2);
	}
	STOP_TIMER("File Read");

	START_TIMER;
	Sort();
	STOP_TIMER("Sort");

	return true;
}

void Graph::AddEdge(unsigned int node1, unsigned int node2)
{
	m_EdgesCount++;
}

// Garante que os vizinhos estejam ordenados do menor para o maior
void Graph::Sort()
{
}

void Graph::BreadthFirstSearch(unsigned int startNodeIndex, vector<unsigned int>& parent, vector<int>& level, unsigned int goalNodeIndex)
{
	queue<int> q;
	
	q.push(startNodeIndex);
	int currentLevel = 0;
	parent[startNodeIndex - 1] = 0;
	level[startNodeIndex - 1] = 0;

	while (!q.empty())
	{
		int nodeId = q.front();
		q.pop();
		if (goalNodeIndex == nodeId)
		{
			return;
		}

		for each (int neighborId in GetNeighbors(nodeId))
		{
			if (level[neighborId - 1] != -1)
			{
				continue;
			}
			parent[neighborId - 1] = nodeId;
			level[neighborId - 1] = level[nodeId - 1] + 1;
			q.push(neighborId);
		}
	}
}

void Graph::DepthFirstSearch(unsigned int startNodeIndex, vector<unsigned int> &parent, vector<int> &level, unsigned int goalNodeIndex)
{
	stack<int> stk;

	stk.push(startNodeIndex);

	int currentLevel = 0;
	parent[startNodeIndex - 1] = 0;
	level[startNodeIndex - 1] = currentLevel++;

	while (!stk.empty())
	{
		int nodeId = stk.top();
		stk.pop();
		if (goalNodeIndex == nodeId)
		{
			return;
		}

		if (level[nodeId - 1] != -1)
		{
			continue;
		}
		for each (int neighborId in GetNeighbors(nodeId))
		{
			parent[neighborId - 1] = nodeId;
			level[neighborId - 1] = currentLevel;
			stk.push(neighborId);
		}
		currentLevel++;
	}
}

unsigned int Graph::Distance(unsigned int node1, unsigned int node2)
{
	vector<unsigned int> parent(getNodesCount(), UINT_MAX);
	vector<int> level(getNodesCount(), -1);
	BreadthFirstSearch(node1, parent, level, node2);
	return level[node2 - 1];
}