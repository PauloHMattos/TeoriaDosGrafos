// CaseStudy.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"


list<list<unsigned int>> connectedComponents(ostream* stream, Graph* graph)
{
	INIT_TIMER;
	START_TIMER;
	list<list<unsigned int>> components = graph->GetConnectedComponents();
	STOP_TIMER_I("GetConnectedComponents", 1);

	components.sort();

	*stream << "Numero de componentes: " << components.size() << "\n";
	*stream << "Tamanho da maior componentes " << components.back().size() << "\n";
	*stream << "Tamanho da menor componentes " << components.front().size() << "\n";
	*stream << "\n";

	return components;
}

void diameter(Graph* graph)
{
	INIT_TIMER;
	START_TIMER;
	
	auto diameter = graph->FindDiameter();
	STOP_TIMER_I("FindDiameter", 1);

	cout << "Diametro do grafo(): " << diameter << "\n";
	cout << "\n";
}

void distance(Graph* graph)
{
	unsigned int dist = graph->Distance(10, 20);
	cout << "Distancia (10, 20): " << dist << "\n";
	dist = graph->Distance(10, 30);
	cout << "Distancia (10, 30): " << dist << "\n";
	dist = graph->Distance(20, 30);
	cout << "Distancia (20, 30): " << dist << "\n";
	cout << "\n";
}

void stats(ostream* stream, Graph* graph)
{
	*stream << "Grau minimo: " << graph->getMinDegree() << "\n";
	*stream << "Grau maximo: " << graph->getMaxDegree() << "\n";
	*stream << "Grau medio: " << graph->getMeanDegree() << "\n";
	*stream << "Mediana do grau: " << graph->getMedianDegree() << "\n";
	*stream << "\n";
	connectedComponents(stream, graph);
}

void findParentBFS(Graph* graph, unsigned int goal)
{
	for (unsigned int i = 1; i <= 3; i++)
	{
		vector<unsigned int> parent(graph->getNodesCount(), UINT_MAX);
		vector<int> level(graph->getNodesCount(), -1);
		graph->BreadthFirstSearch(i, parent, level);
		cout << "Parent(BFS, " << i << ", " << goal << "): " << parent[goal - 1] << "\n";
	}
	cout << "\n";
}

void findParentDFS(Graph* graph, unsigned int goal)
{
	for (unsigned int i = 1; i <= 3; i++)
	{
		vector<unsigned int> parent(graph->getNodesCount(), UINT_MAX);
		vector<int> level(graph->getNodesCount(), -1);
		graph->DepthFirstSearch(i, parent, level);
		cout << "Parent(DFS, " << i << ", " << goal << "): " << parent[goal - 1] << "\n";
	}
	cout << "\n";
}

void findParentBFS(Graph* graph)
{
	findParentBFS(graph, 10);
	findParentBFS(graph, 20);
	findParentBFS(graph, 30);
}

void findParentDFS(Graph* graph)
{
	findParentDFS(graph, 10);
	findParentDFS(graph, 20);
	findParentDFS(graph, 30);
}

void findParent(Graph* graph)
{
	findParentBFS(graph);
	findParentDFS(graph);
}

unsigned int RandU(unsigned int nMin, unsigned int nMax)
{
	return nMin + (unsigned int)((double)rand() / (RAND_MAX + 1) * (nMax - nMin + 1));
}

void timingBFS(Graph* graph, int iterations)
{
	// Fixa uma seed pra que sempre sejam os mesmos
	srand(0);
	INIT_TIMER;
	START_TIMER;

#pragma omp parallel for
	for (int i = 0; i < iterations; i++)
	{
		unsigned int startNode = RandU(1, graph->getNodesCount());
		vector<unsigned int> parent(graph->getNodesCount(), UINT_MAX);
		vector<int> level(graph->getNodesCount(), -1);
		graph->BreadthFirstSearch(startNode, parent, level);

		printf("\r");
	}
	STOP_TIMER_I("Timing BFS", iterations);
	cout << "\n";
}

void timingDFS(Graph* graph, int iterations)
{
	// Fixa uma seed pra que sempre sejam os mesmos
	srand(0);
	INIT_TIMER;
	START_TIMER;

#pragma omp parallel for
	for (int i = 0; i < iterations; i++)
	{
		unsigned int startNode = RandU(1, graph->getNodesCount());
		vector<unsigned int> parent(graph->getNodesCount(), UINT_MAX);
		vector<int> level(graph->getNodesCount(), -1);
		graph->DepthFirstSearch(startNode, parent, level);

		printf("\r");
	}
	STOP_TIMER_I("Timing DFS", iterations);
	cout << "\n";
}

int main()
{
	int dataStructure;
	cout << "Escolha a estrutura de representação do grafo:\n";
	cout << "	1 - Lista de adjacencia;\n";
	cout << "	2 - Matriz de adjacencia;\n";
	cin >> dataStructure;

	Graph* graph;
	if (dataStructure == 1)
	{
		graph = new ListGraph();
	}
	else if (dataStructure == 2)
	{
		graph = new MatrixGraph();
	}
	else
	{
		cout << "Escolha inválida";
		system("pause");
		return 0;
	}


	cout << "Digite o nome do arquivo a ser analizado\n";
	string path;
	cin >> path;

	if (!graph->Load(path))
	{
		cout << "Arquivo não encontrado";
		system("pause");
		return 0;
	}

	//findParent(graph);
	//distance(graph);

	//ofstream outputFile("output_" + path);
	//stats(&outputFile, graph);
	//timingBFS(graph, 1000);
	//timingDFS(graph, 1000);
	diameter(graph);
	/*
	connectedComponents(graph);
	auto components = connectedComponents(graph);
	*/

	system("pause");
	return 0;
}