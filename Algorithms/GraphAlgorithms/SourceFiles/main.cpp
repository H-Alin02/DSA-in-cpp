#include "../../../DataStructures/Graph/HeaderFiles/Graph.h"
#include "../HeaderFiles/GraphAlgoithms.h"
#include <iostream>
using namespace std;

int main(){
    AdjListGraph<int>obj7("text.txt",false);
    obj7.print();
    
    vector<int> dfsResult = GraphAlgorithms<int, AdjListGraph<int>>::DFS(obj7, 0);
    for(int x : dfsResult){
        cout << x << " ";
    }
    cout << endl;

    vector<int> bfsResult = GraphAlgorithms<int, AdjListGraph<int>>::BFS(obj7, 0);
    for(int x : bfsResult){
        cout << x << " ";
    }
    cout << endl;

    return 0;
}