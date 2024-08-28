#include "../../../DataStructures/Graph/HeaderFiles/Graph.h"
#include "../HeaderFiles/GraphAlgoithms.h"
#include <iostream>
using namespace std;

int main(){
    AdjListGraph<int>graph("text.txt",true);
    graph.print();
    
    auto dfsResult = GraphAlgorithms<int, AdjListGraph<int>>::DFS(graph);

    // Stampa dei risultati della DFS
    for (const auto& [componentIndex, component] : dfsResult) {
        cout << "Component DFS " << componentIndex << ": ";
        for (int node : component) {
            cout << node << " ";
        }
        cout << endl;
    }

    // Esecuzione della BFS per tutte le componenti connesse
    auto bfsResult = GraphAlgorithms<int, AdjListGraph<int>>::BFS(graph);

    // Stampa dei risultati della BFS
    for (const auto& [componentIndex, component] : bfsResult) {
        cout << "Component BFS " << componentIndex << ": ";
        for (int node : component) {
            cout << node << " ";
        }
        cout << endl;
    }

    stack<int> topoResult = GraphAlgorithms<int, AdjListGraph<int>>::ReversePostTopologicalSort(graph);
    cout << "Topological Sort: ";
    while (!topoResult.empty()) {
        cout << topoResult.top() << " ";
        topoResult.pop();
    }
    cout << endl;

    vector<int> topoResult2 = GraphAlgorithms<int, AdjListGraph<int>>::KahnTopologicalSort(graph);
    cout << "Topological Sort: ";
    for (int node : topoResult2) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}