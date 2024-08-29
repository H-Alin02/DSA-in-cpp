#ifndef _UNIONFIND_
#define _UNIONFIND_

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <list>
#include <algorithm>
using namespace std;

template <typename T>
class UnionFind{
    private:
        vector<T> parents;
        vector<int> size;
        int numSets;

    public:
        UnionFind(int n){
            numSets = n;
            parents.resize(n);
            size.resize(n,1);
            for(int i = 0; i < n; i++){
                parents[i] = i;
            }
        }

        T find(T x){
            if(x != parents[x]){
                // Path Compression
                parents[x] = find(parents[x]);
            }
            return parents[x];
        }

        void UnionBySize(T x, T y){
            T xRoot = find(x);
            T yRoot = find(y);
            if(xRoot == yRoot){
                return;
            }
            if(size[xRoot] < size[yRoot]){
                parents[xRoot] = yRoot;
                size[yRoot] += size[xRoot];
            }
            else{
                parents[yRoot] = xRoot;
                size[xRoot] += size[yRoot];
            }
            numSets--;
        }

        void print(){
            cout << "Sets: " << numSets << endl;

            cout << "Size: [";
            for(int i = 0; i < size.size(); i++){
                cout << size[i] << "|";
            }
            cout << "]" << "\n";
            
            cout << "Parents: [";
            for(int i = 0; i < parents.size(); i++){
                cout << parents[i] << "|";
            }
            cout << "]" << "\n\n";

            printForest();
            
        }

        void printForest() const {
            cout << "Forest of Trees (Union-Find Structure):" << endl;

            // Trova tutti i rappresentanti (radici degli alberi)
            for (int i = 0; i < parents.size(); ++i) {
                if (parents[i] == i) {  // È un rappresentante
                    printTree(i, 0);
                    cout << endl;  // Separazione tra diversi alberi
                }
            }
        }

        void printTree(int node, int depth) const {
            // Stampiamo l'identazione per la profondità
            for (int i = 0; i < depth; ++i) {
                cout << "\t";
            }

            // Stampiamo il nodo corrente
            cout << node << endl;

            // Stampiamo i figli del nodo corrente
            for (int i = 0; i < parents.size(); ++i) {
                if (parents[i] == node && i != node) {
                    printTree(i, depth + 1);
                }
            }
        }

};
#endif