#include "../../../DataStructures/Graph/HeaderFiles/WeightedGraph.h"
#include "../HeaderFiles/GraphAlgoithms.h"
#include <iostream>
using namespace std;

int main(){
    AdjListWeightedGraph<int> graph1("MST.txt");
    graph1.print();
    
    auto result1 = GraphAlgorithms<int, AdjListWeightedGraph<int>>::KruskalMST(graph1);
    
    cout << "Kruskal MST 1, cost: "<< result1.second << endl;
    for(auto i : result1.first){
        cout << "(" << i.first.first << "," << i.first.second << ")" << "=" << i.second << endl;
    }
    cout << endl;

    return 0;
}