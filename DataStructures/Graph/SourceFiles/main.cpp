#include "../HeaderFiles/Graph.h"
#include <iostream>
using namespace std;

int main(){

    // Graph as Adjacency Matrix
    AdjMatGraph<int>* obj1 = new AdjMatGraph<int>(6);
    AdjMatGraph<int>* obj2 = new AdjMatGraph<int>(6,6);
    AdjMatGraph<int>* obj3 = new AdjMatGraph<int>("text.txt");

    // Graph as Adjacency List
    AdjListGraph<int>* obj4 = new AdjListGraph<int>(6);
    AdjListGraph<int>* obj5 = new AdjListGraph<int>(*obj2);
    AdjListGraph<int>* obj6 = new AdjListGraph<int>("text.txt");

    obj1->print();
    obj4->print();

    obj2->print();
    obj5->print();
    
    obj3->print();
    obj6->print();

    vector<pair<int,int>> edges {{0,1},{0,2},{1,3},{1,4},{2,3},{2,4},{3,5},{4,5}};
    obj1->insert(edges);
    obj1->print();
    cout << "Adjacent (0,1): " << obj1->adjacent(0,1) << endl;
    cout << "Adjacent (2,1): " << obj1->adjacent(2,1) << endl;

    vector<int> neighbous = obj1->Neighbours(1);
    cout << "Neighbours of 1: ";
    for (auto i : neighbous) cout << i << " ";
    cout << "\n\n";

    cout << "Degree of 1: " << obj1->degree(1) << "\n\n";

    edges = {{0,1},{0,2},{1,3},{1,4},{2,3},{2,4},{3,5},{4,5}};
    obj4->insert(edges);
    obj4->print();
    cout << "Adjacent (0,1): " << obj4->adjacent(0,1) << endl;
    cout << "Adjacent (2,1): " << obj4->adjacent(2,1) << endl;

    neighbous = obj4->Neighbours(1);
    cout << "Neighbours of 1: ";
    for (auto i : neighbous) cout << i << " ";
    cout << "\n\n";

    cout << "Degree of 1: " << obj4->degree(1) << "\n\n";
    

    delete obj1;
    delete obj2;
    delete obj3;
    delete obj4;
    delete obj5;
    delete obj6;

    return 0;
}