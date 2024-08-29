#include "../HeaderFiles/WeightedGraph.h"
#include <iostream>
using namespace std;

int main(){

    AdjMatWeightedGraph<int> obj1(4);
    AdjMatWeightedGraph<int> obj2(4,4);
    AdjMatWeightedGraph<int> obj3("text2.txt");
    obj1.insert(0,1,1);
    obj1.insert(1,2,2);
    obj1.insert(2,3,3);
    obj1.insert(3,0,4);
    obj1.print();obj2.print();obj3.print();

    AdjListWeightedGraph<int> obj4(4);
    AdjListWeightedGraph<int> obj6("text2.txt");
    obj4.insert(0,1,1);
    obj4.insert(1,2,2);
    obj4.insert(2,3,3);
    obj4.insert(3,0,4);
    obj4.print();obj6.print();

    return 0;
}