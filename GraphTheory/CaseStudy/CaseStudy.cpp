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

	//if (!graph->Load("C:\\Users\\Paulo\\Documents\\GitHub\\TeoriaDosGrafos\\GraphTheory\\x64\\Debug\\as_graph.txt"))
	if (!graph->Load("C:\\Users\\Paulo\\Documents\\GitHub\\TeoriaDosGrafos\\GraphTheory\\x64\\Debug\\dblp.txt"))
	{
		cout << "Arquivo não encontrado";
		system("pause");
		return 0;
	}

	cout << "Numero de vertices: " << graph->getNodesCount() << "\n";
	cout << "Numero de arestas: " << graph->getEdgesCount() << "\n";
	system("pause");

	vector<bool> visited(graph->getNodesCount());
	vector<int> parent(graph->getNodesCount());
	vector<int> level(graph->getNodesCount());

	INIT_TIMER;
	START_TIMER;
	graph->DepthFirstSearch(1, visited, parent, level);
	STOP_TIMER("DFS");
	system("pause");
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
