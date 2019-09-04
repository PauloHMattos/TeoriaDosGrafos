#include "pch.h"
#include "Graph.h"

#include <fstream>
#include <queue>
#include <stack>
#include <iostream>
#include <climits>
#include <omp.h>
#include <iterator>

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

void Graph::BreadthFirstSearch(unsigned int startNodeIndex, vector<unsigned int>& parent, vector<int>& level)
{
	if (startNodeIndex > m_NodesCount)
	{
		return;
	}

	queue<unsigned int> q;
	
	q.push(startNodeIndex);
	parent[startNodeIndex - 1] = 0;
	level[startNodeIndex - 1] = 0;

	while (!q.empty())
	{
		auto nodeId = q.front();
		q.pop();

		for (unsigned int i = 0; i < m_Degrees[nodeId - 1]; i++)
		{
			auto neighborId = GetNeighbor(nodeId, i);
		
			if (parent[neighborId - 1] != UINT_MAX)
			{
				continue;
			}
			parent[neighborId - 1] = nodeId;
			level[neighborId - 1] = level[nodeId - 1] + 1;
			q.push(neighborId);
		}
	}
}

void Graph::DepthFirstSearch(unsigned int startNodeIndex, vector<unsigned int> &parent, vector<int> &level)
{
	if (startNodeIndex > m_NodesCount)
	{
		return;
	}

	vector<bool> mark = vector<bool>(getNodesCount(), false);
	stack<unsigned int> stk;

	stk.push(startNodeIndex);


	parent[startNodeIndex - 1] = 0;
	level[startNodeIndex - 1] = 0;

	while (!stk.empty())
	{
		auto nodeId = stk.top();
		stk.pop();

		if (mark[nodeId - 1])
		{
			continue;
		}

		mark[nodeId - 1] = true;
		for (unsigned int i = 0; i < m_Degrees[nodeId - 1]; i++)
		{
			auto neighborId = GetNeighbor(nodeId, i);
			if (parent[neighborId - 1] == UINT_MAX)
			{
				parent[neighborId - 1] = nodeId;
				level[neighborId - 1] = level[nodeId - 1] + 1;
			}
			stk.push(neighborId);
		}
	}
}

list<list<unsigned int>> Graph::GetConnectedComponents()
{
	// Guarda os ponteiros
	auto map = vector<list<unsigned int>*>(getNodesCount());
	auto components = list<list<unsigned int>>();

	vector<unsigned int> parent(getNodesCount(), UINT_MAX);

	for (unsigned int nodeId = 1; nodeId < getNodesCount() + 1; nodeId++)
	{
		if (parent[nodeId - 1] != UINT_MAX)
		{
			continue;
		}
		DFSUtil(nodeId, parent);

		components.push_front(list<unsigned int>());

		map[nodeId - 1] = &*components.begin();
		map[nodeId - 1]->push_front(nodeId);
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
		map[parent[nodeId] - 1]->push_front(nodeId + 1);
	}

	return components;
}

unsigned int Graph::Distance(unsigned int node1, unsigned int node2)
{
	if (node1 > m_NodesCount || node2 > m_NodesCount)
	{
		return UINT_MAX;
	}

	vector<int> level(getNodesCount(), -1);
	BFSUtil(node1, level, node2);
	return level[node2 - 1];
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
	
	for (unsigned int degree : m_Degrees)
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
	
	for (unsigned int degree : m_Degrees)
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
	return (float)m_EdgesCount / (float)m_NodesCount;
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
		//sort(degrees.begin(), degrees.end());

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
	stack<unsigned int> stk;

	stk.push(startNodeIndex);

	parent[startNodeIndex - 1] = 0;

	while (!stk.empty())
	{
		unsigned int nodeId = stk.top();
		stk.pop();
		
		for (unsigned int i = 0; i < m_Degrees[nodeId - 1]; i++)
		{
			auto neighborId = GetNeighbor(nodeId, i);

			if (parent[neighborId - 1] != UINT_MAX)
			{
				continue;
			}

			parent[neighborId - 1] = startNodeIndex;
			stk.push(neighborId);
		}
	}
}

unsigned int Graph::BFSUtil(unsigned int startNodeIndex, vector<int>& level, unsigned int goalIndex)
{
	unsigned int diameter = 0;
	queue<unsigned int> q;

	q.push(startNodeIndex);
	level[startNodeIndex - 1] = 0;

	while (!q.empty())
	{
		unsigned int nodeId = q.front();
		q.pop();
		if (goalIndex == nodeId)
		{
			return diameter;
		}
		
		for (unsigned int i = 0; i < m_Degrees[nodeId - 1]; i++)
		{
			auto neighborId = GetNeighbor(nodeId, i);

			if (level[neighborId - 1] != -1)
			{
				continue;
			}


			level[neighborId - 1] = level[nodeId - 1] + 1;
			if ((unsigned int)level[neighborId - 1] > diameter)
			{
				diameter = level[neighborId - 1];
			}
			q.push(neighborId);
		}
	}
	return diameter;
}

unsigned int Graph::FindDiameter(list<list<unsigned int>> components)
{
	unsigned int diameter = 0;

	list<unsigned int> largestComponent = *components.end();
	list<unsigned int>::iterator it;

//#pragma omp parallel for shared(diameter)
	for (it = largestComponent.begin(); it != largestComponent.end(); ++it)
	{
		auto nodeId = *it;
		vector<int> level(getNodesCount(), -1);
		auto d = BFSUtil(nodeId, level, UINT_MAX);
		if (d > diameter)
		{
			diameter = d;
		}
	}
	return diameter;
}
/*
unsigned int Graph::FindDiameter()
{
	// O(n^2)
	unsigned int diameter = 0;
	
	for (unsigned int node1 = 1; node1 < getNodesCount() + 1; node1++)
	{
		for (unsigned int node2 = 1; node2 < getNodesCount() + 1; node2++)
		{
			auto d = Distance(node1, node2);
			if (d > diameter)
			{
				diameter = d;
			}
		}
	}
	return diameter;
}
*/
/*
unsigned int Graph::FindDiameter()
{
	// O(n^2)
	unsigned int diameter = 0;
	for (unsigned int nodeId = 1; nodeId < getNodesCount() + 1; nodeId++)
	{
		vector<int> level(getNodesCount(), -1);
		queue<unsigned int> q;
		q.push(nodeId);

		while (!q.empty())
		{
			auto nId = q.front();
			q.pop();

			for each (int neighborId in GetNeighbors(nId))
			{
				if (level[neighborId - 1] != -1)
				{
					continue;
				}

				level[neighborId - 1] = level[nId - 1] + 1;
				if (level[neighborId - 1] > diameter)
				{
					diameter = level[neighborId - 1];
				}
				q.push(neighborId);
			}
		}
	}
	return diameter;
}
*/