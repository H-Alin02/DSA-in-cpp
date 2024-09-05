#include "../../../DataStructures/Graph/HeaderFiles/WeightedGraph.h"
#include "../HeaderFiles/GraphAlgoithms.h"
#include <iostream>
using namespace std;

int main(){
    AdjListWeightedGraph<int> graph1("Dijkstra.txt");
    graph1.print();
    
    auto result1 = GraphAlgorithms<int, AdjListWeightedGraph<int>>::dijkstra(0,1,graph1);
    cout << "Dijstra from 0 to 1: "<< result1 << endl;
    result1 = GraphAlgorithms<int, AdjListWeightedGraph<int>>::dijkstra(0,2,graph1);
    cout << "Dijstra from 0 to 2: "<< result1 << endl;
    result1 = GraphAlgorithms<int, AdjListWeightedGraph<int>>::dijkstra(0,3,graph1);
    cout << "Dijstra from 0 to 3: "<< result1 << endl;
    result1 = GraphAlgorithms<int, AdjListWeightedGraph<int>>::dijkstra(0,4,graph1);
    cout << "Dijstra from 0 to 4: "<< result1 << endl;
 
    return 0;
}