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
	m_Degrees[node1 - 1] += 1;
	m_Degrees[node2 - 1] += 1;
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
	level[startNodeIndex - 1] = 0;

	while (!stk.empty())
	{
		int nodeId = stk.top();
		stk.pop();
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
			stk.push(neighborId);
		}
	}
}

forward_list<forward_list<int>> Graph::GetConnectedComponents()
{
	// Guarda os ponteiros
	auto map = vector<forward_list<int>*>(getNodesCount());
	auto components = forward_list<forward_list<int>>();

	vector<unsigned int> parent(getNodesCount(), UINT_MAX);

	for (unsigned int nodeId = 1; nodeId < getNodesCount() + 1; nodeId++)
	{
		if (parent[nodeId - 1] != UINT_MAX)
		{
			continue;
		}

		auto component = forward_list<int>();
		component.push_front(nodeId);

		DFSUtil(nodeId, parent);
		
		map[nodeId - 1] = &component;
		components.push_front(component);
	}

	for (unsigned int nodeId = 0; nodeId < getNodesCount(); nodeId++)
	{
		if (parent[nodeId] == UINT_MAX)
		{
			continue;
		}

		if (parent[nodeId] == 0)
		{
			continue;
		}

		auto component = *map[parent[nodeId] - 1];
		component.push_front(nodeId);
	}

	return components;
}

unsigned int Graph::Distance(unsigned int node1, unsigned int node2)
{
	vector<int> level(getNodesCount(), -1);
	BFSUtil(node1, level, node2);
	return level[node2 - 1];
}

unsigned int Graph::FindDiameter()
{
	// O(n^2 log n)
	int diameter = -1;
	for (unsigned int nodeId = 0; nodeId < getNodesCount(); nodeId++)
	{
		vector<int> level(getNodesCount(), -1);
		BFSUtil(nodeId, level, UINT_MAX);

		if (level[nodeId] > diameter)
		{
			diameter = level[nodeId];
		}
	}
	return diameter;
}

unsigned int Graph::getDegree(unsigned int nodeIndex)
{
	if (nodeIndex > m_NodesCount)
	{
		return UINT_MAX;
	}
	return m_Degrees[nodeIndex - 1];
}

unsigned int Graph::getMinDegree()
{
	unsigned int result = UINT_MAX;
	for each (unsigned int degree in m_Degrees)
	{
		if (degree < result)
		{
			result = degree;
		}
	}
	return result;
}

unsigned int Graph::getMaxDegree()
{
	unsigned int result = 0;
	for each (unsigned int degree in m_Degrees)
	{
		if (degree > result)
		{
			result = degree;
		}
	}
	return result;
}

float Graph::getMeanDegree()
{
	if (m_NodesCount == 0)
	{
		return 0;
	}
	return m_EdgesCount / m_NodesCount;
}

unsigned int Graph::getMedianDegree()
{
	int size = m_Degrees.size();

	if (size == 0)
	{
		return 0;
	}
	else
	{
		// Cria uma cópia para não alterar o vetor original
		vector<unsigned int> degrees(m_Degrees);
		sort(degrees.begin(), degrees.end());

		if (size % 2 == 0)
		{
			return (degrees[size / 2 - 1] + degrees[size / 2]) / 2;
		}
		else
		{
			return degrees[size / 2];
		}
	}
}



void Graph::Resize(unsigned int count)
{
	m_Degrees = vector<unsigned int>(count);
}


void Graph::DFSUtil(unsigned int startNodeIndex, vector<unsigned int>& parent)
{
	stack<int> stk;

	stk.push(startNodeIndex);

	int currentLevel = 0;
	parent[startNodeIndex - 1] = 0;

	while (!stk.empty())
	{
		int nodeId = stk.top();
		stk.pop();

		for each (int neighborId in GetNeighbors(nodeId))
		{
			if (parent[neighborId - 1] != UINT_MAX)
			{
				continue;
			}

			parent[neighborId - 1] = startNodeIndex;
			stk.push(neighborId);
		}
	}
}

void Graph::BFSUtil(unsigned int startNodeIndex, vector<int>& level, unsigned int goalIndex)
{
	queue<int> q;

	q.push(startNodeIndex);
	int currentLevel = 0;
	level[startNodeIndex - 1] = 0;

	while (!q.empty())
	{
		int nodeId = q.front();
		q.pop();
		if (goalIndex == nodeId)
		{
			return;
		}

		for each (int neighborId in GetNeighbors(nodeId))
		{
			if (level[neighborId - 1] != -1)
			{
				continue;
			}
			level[neighborId - 1] = level[nodeId - 1] + 1;
			q.push(neighborId);
		}
	}
}
