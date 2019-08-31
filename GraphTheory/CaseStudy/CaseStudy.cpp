// CaseStudy.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <chrono>
#include "Graph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"


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
	//cin >> path;

	if (!graph->Load("C:\\Users\\Paulo\\Documents\\GitHub\\TeoriaDosGrafos\\GraphTheory\\x64\\Debug\\as_graph.txt"))
	//if (!graph->Load("C:\\Users\\Paulo\\Documents\\GitHub\\TeoriaDosGrafos\\GraphTheory\\x64\\Debug\\live_journal.txt"))
	{
		cout << "Arquivo não encontrado";
		system("pause");
		return 0;
	}

	cout << "Numero de vertices: " << graph->getNodesCount() << "\n";
	cout << "Numero de arestas: " << graph->getEdgesCount() << "\n";
	//system("pause");


	INIT_TIMER;

	int runCnt = 500;
	//*
	START_TIMER;
	for (int i = 0; i < runCnt; i++)
	{
		vector<bool> visited(graph->getNodesCount());
		vector<int> parent(graph->getNodesCount());
		vector<int> level(graph->getNodesCount());
		graph->BreadthFirstSearch(1, visited, parent, level);
	}
	STOP_TIMER_I("BFS", runCnt);
	//*/
	//*
	START_TIMER;
	for (int i = 0; i < runCnt; i++)
	{
		vector<bool> visited(graph->getNodesCount());
		vector<int> parent(graph->getNodesCount());
		vector<int> level(graph->getNodesCount());
		graph->DepthFirstSearch(1, visited, parent, level);
	}
	STOP_TIMER_I("DFS", runCnt);
	//*/
	system("pause");

	return 0;
}