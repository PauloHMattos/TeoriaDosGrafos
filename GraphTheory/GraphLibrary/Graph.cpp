#include "pch.h"
#include "Graph.h"

#include <fstream>
#include <queue>
#include <stack>
#include <iostream>

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

void Graph::AddEdge(int node1, int node2)
{
	m_EdgesCount++;
}

// Garante que os vizinhos estejam ordenados do menor para o maior
void Graph::Sort()
{
}

void Graph::BreadthFirstSearch(int startNodeIndex, vector<bool> visited, vector<int> parent, vector<int> level)
{
	queue<int> q;
	
	q.push(startNodeIndex);
	visited[startNodeIndex - 1] = true;

	int currentLevel = 0;
	parent[startNodeIndex - 1] = 0;
	level[startNodeIndex - 1] = currentLevel++;

	while (!q.empty())
	{
		int nodeId = q.front();
		q.pop();

		forward_list<int>::iterator it;
		forward_list<int> neighbors = GetNeighbors(nodeId);

		for (it = neighbors.begin(); it != neighbors.end(); ++it)
		{
			int neighborId = *it - 1;
			if (visited[neighborId])
			{
				continue;
			}
			visited[neighborId] = true;
			q.push(*it);

			parent[neighborId] = nodeId;
			level[neighborId] = currentLevel;
		}
		currentLevel++;
	}
}

void Graph::DepthFirstSearch(int startNodeIndex, vector<bool> visited, vector<int> parent, vector<int> level)
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

		if (visited[nodeId - 1])
		{
			continue;
		}
		visited[nodeId - 1] = true;

		forward_list<int>::iterator it;
		forward_list<int> neighbors = GetNeighbors(nodeId);

		for (it = neighbors.begin(); it != neighbors.end(); ++it)
		{
			int neighborId = *it - 1;
			visited[neighborId] = true;
			stk.push(*it);

			parent[neighborId] = nodeId;
			level[neighborId] = currentLevel;
		}
		currentLevel++;
	}
}