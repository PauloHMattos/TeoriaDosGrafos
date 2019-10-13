#include <iostream>
#include <chrono>
#include "Graph.h"
#include "WeightedGraph.h"
#include <fstream>
#include <map>
#include "CaseStudy.h"
#include <iomanip>      // std::setprecision

int caseStudy2(string path, string labelsPath);


int main()
{
	/*
	cout << "Digite o nome do arquivo a ser analizado\n";
	string path;
	cin >> path;

	cout << "Digite o nome do arquivo de rotulos\n";
	string labelspath;
	cin >> labelspath;
	//*/

	string path = "C:/Users/Paulo/Documents/GitHub/TeoriaDosGrafos/GraphTheory/x64/Debug/grafo_1.txt";
	string labelsPath = "C:/Users/Paulo/Documents/GitHub/TeoriaDosGrafos/GraphTheory/x64/Debug/rede_colaboracao_vertices.txt";

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


	return caseStudy2(path, labelsPath);
}

void distColab(WeightedGraph& graph);
void eccentricity(WeightedGraph& graph);
void timingEccentricity(WeightedGraph& graph, int iterations);
void mstPrim(WeightedGraph& graph);
void mstKruskal(WeightedGraph& graph);
void mstCollab(WeightedGraph& graph);

int caseStudy2(string path, string labelsPath)
{
	WeightedGraph graph;
	graph.Load(path);
	//graph.LoadLabels(labelsPath);

	//distColab(graph);
	//mstCollab(graph);
	mstPrim(graph);
	mstKruskal(graph);
	eccentricity(graph);
	timingEccentricity(graph, 100);

	/*
	double weight = 0;
	auto tree = graph.MinimumSpanningTree(&weight);
	//*/
	system("PAUSE");
	return 0;
}

void eccentricity(WeightedGraph& graph)
{
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
}

void timingEccentricity(WeightedGraph& graph, int iterations)
{
	srand(0);
	INIT_TIMER;
	START_TIMER;

#pragma omp parallel for
	for (int i = 0; i < iterations; i++)
	{
		unsigned int startNode = RandU(1, graph.getNodesCount());
		graph.Eccentricity(startNode);
		cout << i << "             ";
		printf("\r");
	}

	STOP_TIMER_I("Timing Eccentricity", iterations);
	cout << "\n";
}

void mstPrim(WeightedGraph& graph)
{
	INIT_TIMER;
	START_TIMER;

	double weight = 0;
	auto tree = graph.MinimumSpanningTree(&weight, 1);

	STOP_TIMER("MST Prim");
	cout << "Peso: " << weight;

	cout << "\n";

	// TODO - Salvar num arquivo de texto
}

void mstKruskal(WeightedGraph& graph)
{
	INIT_TIMER;
	START_TIMER;

	double weight = 0;
	auto tree = graph.MinimumSpanningTree(&weight, 0);

	STOP_TIMER("MST Kruskal");
	cout << "Peso: " << weight;

	cout << "\n";

	// TODO - Salvar num arquivo de texto
}

void distColab(WeightedGraph& graph)
{
	cout << "\n";
	cout << "Distancia de colaboradores\n";
	//						11365			471365				5709			11386				34930
	string labels[] = { "Alan M. Turing", "J. B. Kruskal", "Jon M. Kleinberg", "Éva Tardos", "Daniel R. Figueiredo" };
	auto dijkstra = graph.FindByLabel("Edsger W. Dijkstra"); // 2722
	
	for (int i = 0; i < 5; i++)
	{
		auto other = graph.FindByLabel(labels[i]);

		list<unsigned int> path;
		auto dist = graph.Distance(dijkstra, other, path);

		cout << labels[i] << "\n";
		cout << "Distancia: " << dist << " - ";
		for (unsigned int node : path)
		{
			cout << graph.getLabel(node) << ", ";
		}
		cout << "\n";
		cout << "\n";
	}
}

void mstCollab(WeightedGraph& graph)
{
	auto dijkstra = graph.FindByLabel("Edsger W. Dijkstra"); // 2722
	auto figueiredo = graph.FindByLabel("Daniel R. Figueiredo"); // 343930

	double weight = 0;
	auto tree = graph.MinimumSpanningTree(&weight, 2722);

	auto table = map<unsigned int, list<Edge>>();

	unsigned int maxDegreeOwner = 0;
	unsigned int maxDegree = 0;
	for (auto p : tree)
	{
		if (p.first == 0)
		{
			continue;
		}

		if (p.first - 1 >= table.size())
		{
			table.insert(make_pair(p.first - 1, list < Edge>()));
		}
		table[p.first - 1].push_front(p.second);

		if (table[p.first - 1].size() > maxDegree)
		{
			maxDegreeOwner = p.first;
			maxDegree = table[p.first - 1].size();
		}
	}
	
	auto a = table[dijkstra - 1];
	auto b = table[figueiredo - 1];

	int i = 0;
}