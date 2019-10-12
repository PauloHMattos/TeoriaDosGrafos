#include <iostream>
#include <chrono>
#include "Graph.h"
#include "WeightedGraph.h"
#include <fstream>
#include "CaseStudy.h"

int main()
{
	/*
	cout << "Digite o nome do arquivo a ser analizado\n";
	string path;
	cin >> path;*/

	string path = "C:/Users/Paulo/Documents/GitHub/TeoriaDosGrafos/GraphTheory/x64/Debug/grafo_2.txt";
	ifstream file(path);

	if (!file)
	{
		return false;
	}

	unsigned int nodesCount;
	file >> nodesCount;

	
	string firstEdge;
	for (int i = 0; i < 2; i++)
	{
		std::getline(file, firstEdge);
	}

	file.close();

	int i = 0;
	for (char character : firstEdge)
	{
		if (character == ' ')
		{
			i++;
		}
	}

	if (i < 2)
	{
		return caseStudy1(path);
	}

	return caseStudy2(path);
}

int caseStudy2(string path)
{
	WeightedGraph graph;
	graph.Load(path);
	/*
	unsigned int startNode = 1;
	unsigned int destinations[] = { 10, 20, 30, 40, 50 };
	for (int i = 0; i < sizeof(destinations) / sizeof(unsigned int); i++)
	{
		list<unsigned int> path;
		auto dist = graph.Distance(startNode, destinations[i], path);

		cout << "Distancia: " << dist << " - ";
		for (unsigned int node : path)
		{
			cout << node << ", ";
		}
		cout << "\n";

		auto ecc = graph.Eccentricity(destinations[i]);
		cout << "Excentricidade: " << ecc << "\n";


		cout << "\n\n";
	}
	//*/

	float weight = 0;
	auto tree = graph.MinimumSpanningTree(&weight);

	return 0;
}