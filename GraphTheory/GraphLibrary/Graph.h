#pragma once

#include <string>
#include <forward_list>
#include <vector>

#ifdef GRAPHLIBRARY_EXPORTS
#define GRAPHLIBRARY_API __declspec(dllexport)
#else
#define GRAPHLIBRARY_API __declspec(dllimport)
#endif

using namespace std;

class GRAPHLIBRARY_API Graph
{
public:
	bool Load(string path);
	virtual void AddNode(unsigned int index) = 0;
	virtual void AddEdge(unsigned int node1, unsigned int node2);
	virtual void Sort();

	void BreadthFirstSearch(unsigned int startNodeIndex, vector<unsigned int>& parent, vector<int>& level, unsigned int goalNodeIndex = UINT_MAX);
	void DepthFirstSearch(unsigned int startNodeIndex, vector<unsigned int>& parent, vector<int>& level, unsigned int goalNodeIndex = UINT_MAX);

	unsigned int Distance(unsigned int node1, unsigned int node2);
	unsigned int FindDiameter();


	forward_list<forward_list<int>> GetConnectedComponents();


	virtual forward_list<int> GetNeighbors(unsigned int nodeIndex) = 0;


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


	vector<unsigned int> m_Degrees;

	unsigned int m_NodesCount = 0;
	unsigned int m_EdgesCount = 0;
};


#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now()
#define START_TIMER  start = std::chrono::high_resolution_clock::now()

#define STOP_TIMER(name)  std::cout << "RUNTIME of " << name << ": " << \
    std::chrono::duration_cast<std::chrono::milliseconds>( \
            (std::chrono::high_resolution_clock::now()-start) \
    ).count() << " ms " << std::endl

#define STOP_TIMER_I(name, d)  std::cout << "RUNTIME of " << name << ": " << \
    std::chrono::duration_cast<std::chrono::milliseconds>( \
            (std::chrono::high_resolution_clock::now()-start) / d \
    ).count() << " ms " << std::endl