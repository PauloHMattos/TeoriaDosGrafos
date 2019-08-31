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

unsigned int Graph::FindDiameter()
{
	unsigned int result = 0;
	for (unsigned int nodeId = 1; nodeId < m_NodesCount + 1; nodeId++)
	{
		unsigned int diameter = FindDiameter(nodeId);
		if (diameter > result)
		{
			result = diameter;
		}
	}
	return result;
}


// TODO - Tem alguma forma de otimizar isso?
unsigned int Graph::FindDiameter(unsigned int startNode)
{
	vector<unsigned int> parent(getNodesCount(), UINT_MAX);
	vector<int> level(getNodesCount(), -1);
	BreadthFirstSearch(startNode, parent, level);

	int diameter = 0;
	for (unsigned int i = 0; i < getNodesCount(); i++)
	{
		if (level[i] > diameter)
		{
			diameter = level[i];
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
