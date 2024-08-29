#include <iostream>
#include "../HeaderFiles/UnionFind.h"
using namespace std;

int main(){
    UnionFind<int> uf = UnionFind<int>(6);
    uf.print();
    
    uf.UnionBySize(0,1);
    uf.print();
    
    uf.UnionBySize(2,3);
    uf.print();

    uf.UnionBySize(0,2);
    uf.print();

    uf.UnionBySize(4,5);
    uf.print();

    uf.UnionBySize(1,4);
    uf.print();

    uf.find(3);
    uf.print();

    uf.find(5);
    uf.print();

    return 0;
}