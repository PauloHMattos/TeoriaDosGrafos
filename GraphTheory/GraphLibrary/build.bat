g++ -o CaseStudy.exe -Ofast -Wall -DBUILDING_DLL  Graph.cpp ListGraph.cpp MatrixGraph.cpp CaseStudy.cpp
g++ -o CaseStudy_Parallel.exe -Ofast -Wall -DBUILDING_DLL  Graph.cpp ListGraph.cpp MatrixGraph.cpp CaseStudy.cpp -fopenmp