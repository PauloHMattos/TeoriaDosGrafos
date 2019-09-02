// CaseStudy.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <chrono>
#include "Graph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"


int main()
{
	INIT_TIMER;

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

	//if (!graph->Load("C:\\Users\\Paulo\\Documents\\GitHub\\TeoriaDosGrafos\\GraphTheory\\x64\\Debug\\as_graph.txt"))
	if (!graph->Load("C:\\Users\\Paulo\\Documents\\GitHub\\TeoriaDosGrafos\\GraphTheory\\x64\\Debug\\dblp.txt"))
	//if (!graph->Load("C:\\Users\\Paulo\\Documents\\GitHub\\TeoriaDosGrafos\\GraphTheory\\x64\\Debug\\live_journal.txt"))
	{
		cout << "Arquivo não encontrado";
		system("pause");
		return 0;
	}
	//*
	cout << "Grau minimo: " << graph->getMinDegree() << "\n";
	cout << "Grau máximo: " << graph->getMaxDegree() << "\n";
	cout << "Grau médio: " << graph->getMeanDegree() << "\n";
	cout << "Mediana do grau: " << graph->getMedianDegree() << "\n";
	//*/
	/*
	START_TIMER;
	list<list<unsigned int>> components = graph->GetConnectedComponents();
	STOP_TIMER_I("GetConnectedComponents", 1);

	cout << "Numero de componentes: " << components.size() << "\n";
	/*
	for (list<unsigned int> component : components)
	{
		cout << "Size: " << component.size() << "\n";
		for (unsigned int nodeId : component)
		{
			cout << nodeId << ", ";
		}
		cout << "\n";
		cout << "\n";
	}
	*/
	//*/

	/*
	unsigned int dist = graph->Distance(10, 20);
	cout << "Distancia (10, 20): " << dist << "\n";
	dist = graph->Distance(10, 30);
	cout << "Distancia (10, 30): " << dist << "\n";
	dist = graph->Distance(20, 30);
	cout << "Distancia (20, 30): " << dist << "\n";
	//*/

	/*
	START_TIMER;
	auto diameter = graph->FindDiameter();
	STOP_TIMER_I("FindDiameter", 1);
	cout << "FindDiameter(): " << diameter << "\n";
	return 0;
	//*/
	//*
	int goal = 10;
	vector<unsigned int> parent(graph->getNodesCount(), UINT_MAX);
	vector<int> level(graph->getNodesCount(), -1);
	graph->BreadthFirstSearch(1, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->BreadthFirstSearch(2, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->BreadthFirstSearch(3, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";

	goal = 20;
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->BreadthFirstSearch(1, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->BreadthFirstSearch(2, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->BreadthFirstSearch(3, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";

	goal = 30;
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->BreadthFirstSearch(1, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	level = vector<int>(graph->getNodesCount(), -1);
	graph->BreadthFirstSearch(2, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->BreadthFirstSearch(3, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	//return 0;
	//*/


	goal = 10;
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->DepthFirstSearch(1, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->DepthFirstSearch(2, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->DepthFirstSearch(3, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";

	goal = 20;
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->DepthFirstSearch(1, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->DepthFirstSearch(2, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->DepthFirstSearch(3, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";

	goal = 30;
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->DepthFirstSearch(1, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	level = vector<int>(graph->getNodesCount(), -1);
	graph->DepthFirstSearch(2, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	parent = vector<unsigned int>(graph->getNodesCount(), UINT_MAX);
	level = vector<int>(graph->getNodesCount(), -1);
	graph->DepthFirstSearch(3, parent, level);
	cout << "Parent(" << goal << "): " << parent[goal] << "\n";
	return 0;
	//*/

	int runCnt = 500;
	//*
	START_TIMER;
	for (int i = 0; i < runCnt; i++)
	{
		vector<unsigned int> parent(graph->getNodesCount(), UINT_MAX);
		vector<int> level(graph->getNodesCount(), -1);
		graph->BreadthFirstSearch(1, parent, level);
	}
	STOP_TIMER_I("BFS", runCnt);
	//*/
	//*
	START_TIMER;
	for (int i = 0; i < runCnt; i++)
	{
		vector<unsigned int> parent(graph->getNodesCount(), UINT_MAX);
		vector<int> level(graph->getNodesCount(), -1);
		graph->DepthFirstSearch(1, parent, level);
	}
	STOP_TIMER_I("DFS", runCnt);
	//*/
	system("pause");

	return 0;
}