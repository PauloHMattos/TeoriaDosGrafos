g++ -o CaseStudy.exe -Ofast -w CaseStudy2.cpp dllmain.cpp UnweightedGraph.cpp WeightedGraph.cpp Graph.cpp ListGraph.cpp MatrixGraph.cpp
PAUSE

#g++ -o CaseStudy_Parallel.exe -Ofast -w -DBUILDING_DLL CaseStudy2.cpp dllmain.cpp UnweightedGraph.cpp WeightedGraph.cpp Graph.cpp ListGraph.cpp MatrixGraph.cpp -fopenmp
#PAUSE