#include "pch.h"
#include "Graph.h"

#include <fstream>
#include <queue>
#include <stack>

bool Graph::Load(string path)
{
	ifstream file;
	file.open("C:\\Users\\Paulo\\Documents\\GitHub\\TeoriaDosGrafos\\GraphTheory\\x64\\Debug\\as_graph.txt");
	//file.open(path);

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

	Sort();
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

	startNodeIndex -= 1;

	q.push(startNodeIndex);
	visited[startNodeIndex] = true;

	int currentLevel = 0;
	parent[startNodeIndex] = 0;
	level[startNodeIndex] = currentLevel++;

	while (!q.empty())
	{
		int nodeId = q.front();
		q.pop();

		forward_list<int>::iterator it;
		forward_list<int> neighbors = GetNeighbors(nodeId);

		for (it = neighbors.begin(); it != neighbors.end(); ++it)
		{
			int neighborId = *it;
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

	startNodeIndex -= 1;

	stk.push(startNodeIndex);

	int currentLevel = 0;
	parent[startNodeIndex] = 0;
	level[startNodeIndex] = currentLevel++;

	while (!stk.empty())
	{
		int nodeId = stk.top();
		stk.pop();

		if (visited[nodeId])
		{
			continue;
		}
		visited[nodeId] = true;

		forward_list<int>::iterator it;
		forward_list<int> neighbors = GetNeighbors(nodeId);

		for (it = neighbors.begin(); it != neighbors.end(); ++it)
		{
			int neighborId = *it;
			visited[neighborId] = true;
			stk.push(*it);

			parent[neighborId] = nodeId;
			level[neighborId] = currentLevel;
		}
		currentLevel++;
	}
}