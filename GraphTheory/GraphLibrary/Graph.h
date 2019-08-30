#pragma once

#include <string>
#include <list>

#ifdef GRAPHLIBRARY_EXPORTS
#define GRAPHLIBRARY_API __declspec(dllexport)
#else
#define GRAPHLIBRARY_API __declspec(dllimport)
#endif

using namespace std;

class GRAPHLIBRARY_API Graph
{
public:
	void Load(string path);
	virtual void AddNode(int index) = 0;
	virtual void AddEdge(int node1, int node2);
	/*
	virtual list<int> GetNeighbors(int nodeIndex) = 0;
	
	void BreadthFirstSearch(Tree tree);
	void DepthFirstSearch(Tree tree);
	//*/
	unsigned int getNodesCount() { return m_NodesCount; }
	unsigned int getEdgesCount() { return m_EdgesCount; }

	unsigned int getMinDegree() { return m_MinDegree; }
	unsigned int getMaxDegree() { return m_MaxDegree; }
	unsigned int getMedDegree() { return m_MedDegree; }

protected:
	virtual void Resize(unsigned int count) = 0;
	unsigned int m_NodesCount = 0;
	unsigned int m_EdgesCount = 0;
	unsigned int m_MinDegree = 0;
	unsigned int m_MaxDegree = 0;
	unsigned int m_MedDegree = 0;
};
/*
class Tree
{
public:

};
*/