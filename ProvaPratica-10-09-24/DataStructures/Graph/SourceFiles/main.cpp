#include "../HeaderFiles/Graph.h"
#include <iostream>
using namespace std;

int main(){

    // Graph as Adjacency Matrix
    AdjMatGraph<int> obj1(6,false);
    AdjMatGraph<int>obj2(6,6,false);
    AdjMatGraph<int>obj3("text.txt", true);
    AdjMatGraph<int>obj7("text.txt", false);

    // Graph as Adjacency List
    AdjListGraph<int> obj4(6,false);
    AdjListGraph<int> obj5(obj2);
    AdjListGraph<int> obj6("text.txt", false);

    obj1.print();
    obj4.print();

    obj2.print();
    obj5.print();
    
    AdjMatGraph<int> reverse = obj3.reverseGraph();
    cout <<"Reverse: "<< endl;
    reverse.print();
    cout <<"Directed: "<< endl;
    obj3.print();
    cout <<"Undirected: "<< endl;
    obj7.print();
    obj6.print();

    vector<pair<int,int>> edges {{0,1},{0,2},{1,3},{1,4},{2,3},{2,4},{3,5},{4,5}};
    obj1.insert(edges);
    obj1.print();
    cout << "Adjacent (0,1): " << obj1.adjacent(0,1) << endl;
    cout << "Adjacent (2,1): " << obj1.adjacent(2,1) << endl;

    vector<int> neighbous = obj1.Neighbours(1);
    cout << "Neighbours of 1: ";
    for (auto i : neighbous) cout << i << " ";
    cout << "\n\n";

    cout << "Degree of 1: " << obj1.degree(1) << "\n\n";

    edges = {{0,1},{0,2},{1,3},{1,4},{2,3},{2,4},{3,5},{4,5}};
    obj4.insert(edges);
    obj4.print();
    cout << "Adjacent (0,1): " << obj4.adjacent(0,1) << endl;
    cout << "Adjacent (2,1): " << obj4.adjacent(2,1) << endl;

    neighbous = obj4.Neighbours(1);
    cout << "Neighbours of 1: ";
    for (auto i : neighbous) cout << i << " ";
    cout << "\n\n";

    cout << "Degree of 1: " << obj4.degree(1) << "\n\n";
    return 0;
}