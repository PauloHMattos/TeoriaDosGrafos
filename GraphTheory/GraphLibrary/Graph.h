#pragma once

#include <string>
#include <forward_list>
#include <list>
#include <limits>
#include <vector>
#include "Timing.h"
#include <iterator>

#ifndef UINT_MAX
#define UINT_MAX 0xffffffff
#endif

#ifdef BUILDING_DLL
#define DLL_EXPORT_OR_IMPORT __declspec(dllexport)
#else
#define DLL_EXPORT_OR_IMPORT __declspec(dllimport)
#endif

using namespace std;

class DLL_EXPORT_OR_IMPORT Graph
{
public:
	bool Load(string path);
	virtual void AddNode(unsigned int index) = 0;
	virtual void AddEdge(unsigned int node1, unsigned int node2);
	virtual void Sort();

	void BreadthFirstSearch(unsigned int startNodeIndex, vector<unsigned int>& parent, vector<int>& level);
	void DepthFirstSearch(unsigned int startNodeIndex, vector<unsigned int>& parent, vector<int>& level);

	unsigned int Distance(unsigned int node1, unsigned int node2);
	unsigned int FindDiameter();


	list<list<unsigned int>> GetConnectedComponents();


	virtual unsigned int GetNeighbor(unsigned int nodeIndex, unsigned int neighborId) = 0;


	unsigned int getNodesCount() { return m_NodesCount; }
	unsigned int getEdgesCount() { return m_EdgesCount; }

	unsigned int getDegree(unsigned int nodeIndex);

	unsigned int getMinDegree();
	unsigned int getMaxDegree();
	float getMeanDegree();
	unsigned int getMedianDegree();

protected:
	virtual void Resize(unsigned int count);
	void DFSUtil(unsigned int startNodeIndex, vector<unsigned int>& parent);
	unsigned int BFSUtil(unsigned int startNodeIndex, vector<int>& level, unsigned int goalIndex);
	
	vector<unsigned int> m_Degrees;

	unsigned int m_NodesCount = 0;
	unsigned int m_EdgesCount = 0;
};