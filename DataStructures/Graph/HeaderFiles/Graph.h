#ifndef _GRAPH_
#define _GRAPH_

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <random>
#include <list>
#include <algorithm>
using namespace std;

template<typename T>
class Graph{
    protected:
        int NumV;
        int NumE;

    public:
        virtual bool adjacent(T key1, T key2) = 0;
        virtual void insert(T key1, T key2) = 0;
        virtual void print() = 0;
        virtual vector<T> Neighbours(T key) = 0;
        virtual int degree(T key) = 0;
        virtual void deleteEdge(T key1, T key2) = 0;
        virtual int getEdges() = 0;
        virtual int getVertices() = 0;

};

template<typename T>
class AdjMatGraph : public Graph<T>{

    protected:
        vector<vector<int>> AdjMat;

    public:

        // Create graph with v verticies and 0 edges
        AdjMatGraph(int v){
            this->NumV = v;
            this->NumE = 0;
            AdjMat = vector<vector<int>>(v, vector<int>(v, 0));
        }

        // Create graph with information from file
        AdjMatGraph(string path){
            ifstream infile(path);
            if(!infile){
                cerr << "Error opening file" << endl;
                exit(1);
            }

            // Add vertices
            int v, e;
            infile >> v >> e;
            this->NumV = v;
            this->NumE = e;
            AdjMat = vector<vector<int>>(v, vector<int>(v, 0));

            // Add edges
            T x, y;
            for(int i = 0; i < e; ++i){
                infile >> x >> y;
                insert(x, y);
            }

            infile.close();
        }

        AdjMatGraph(int v, int e){
            this->NumV = v;
            this->NumE = e;
            AdjMat = vector<vector<int>>(v, vector<int>(e, 0));

            random_device rd; 
            mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, v-1);

            for(int i = 0; i < e; ++i){
                int x = dis(gen);
                int y = dis(gen);
                if(!adjacent(x, y))
                insert(x, y);
            }
        }

        ~AdjMatGraph(){}

        bool adjacent(T key1, T key2) override{
            return AdjMat[key1][key2];
        }

        void insert(T key1, T key2) override{
            AdjMat[key1][key2] = 1;
            AdjMat[key2][key1] = 1;
        }

        void insert(vector<pair<T,T>> edges){
            for(pair<T,T> edge : edges){
                insert(edge.first, edge.second);
            }
        }

        void print() override{
            // Prints the Graph matrix            
            cout << "   ";
            for (int i = 0; i < this->NumV; i++)
                cout << i << " ";
            
            cout << endl;

            cout << "   ";
            for (int i = 0; i < this->NumV; i++)
                cout << "- ";
            cout << endl;

            for (int i = 0; i < AdjMat.size(); ++i) {
                cout << i << " |";
                for (int value : AdjMat[i]) {
                    cout << value << " ";
                }
                cout << endl;
            }

            cout << "\n";
        }

        vector<T> Neighbours(T key) override{
            vector<T> neighbours;
            for(int i = 0; i < this->NumV; ++i){
                if(AdjMat[key][i]){
                    neighbours.push_back(i);
                }
            }
            return neighbours;
        }

        int degree(T key) override{
            return Neighbours(key).size();
        }

        void deleteEdge(T key1, T key2){
            AdjMat[key1][key2] = 0;
            AdjMat[key2][key1] = 0;
        }

        int getEdges(){
            return this->NumE;
        }

        int getVertices(){
            return this->NumV;
        } 
    
};

template<typename T>
class AdjListGraph : public Graph<T>{
    
    protected:
        vector<list<T>> AdjList;

    public:

        // Create graph with v verticies and 0 edges
        AdjListGraph(int v){
            this->NumE = v;
            this->NumV = 0;
            AdjList = vector<list<T>>(v, list<T>());
        }

        // Create graph with information from file
        AdjListGraph(string path){
            ifstream infile(path);
            if(!infile){
                cerr << "Error opening file" << endl;
                exit(1);
            }

            // Add vertices
            int v, e;
            infile >> v >> e;
            this->NumV = v;
            this->NumE = e;
            AdjList = vector<list<T>>(v, list<T>());

            // Add edges
            T x, y;
            for(int i = 0; i < e; ++i){
                infile >> x >> y;
                insert(x, y);
            }

            infile.close();
        }

        AdjListGraph(Graph<T>& g){
            this->NumV = g.getVertices();
            this->NumE = g.getEdges();

            AdjList = vector<list<T>>(this->NumV,list<T>());

            for(int i = 0; i < this->NumV; i++){
                vector<T> n = g.Neighbours(i);
                for(int j = 0; j < n.size(); j++){
                    if(!adjacent(i,n[j]))
                        insert(i,n[j]);
                }
            }
        }

        bool adjacent(T key1, T key2) override{
            return find(AdjList[key1].begin(), AdjList[key1].end(), key2) != AdjList[key1].end();
        }

        void insert(T key1, T key2) override{
            if (key1 == key2) {
                if (find(AdjList[key1].begin(), AdjList[key1].end(), key2) == AdjList[key1].end()) {
                    AdjList[key1].push_back(key2);
                }
            } else {
                if (!adjacent(key1, key2)) {
                    AdjList[key1].push_back(key2);
                    AdjList[key2].push_back(key1);
                }
            }
        }

        void insert(vector<pair<T,T>> edges){
            for(pair<T,T> edge : edges){
                insert(edge.first, edge.second);
            }
        }

        void print() override{
            for (int i = 0; i < AdjList.size(); ++i) {
                cout <<"[" << i <<"]" << "-->";
                for (T value : AdjList[i]) {
                    cout <<"[" << value <<"]" " ";
                }
                cout << endl;
            }

            cout << "\n";
        }

        vector<T> Neighbours(T key) override{
            vector<T> neighbours(AdjList[key].begin(), AdjList[key].end());
            return neighbours;
        }

        int degree(T key) override{
            return Neighbours(key).size();
        }

        void deleteEdge(T key1, T key2){
            // Find the iterator that points to key1 in the adjacency list of key2
            auto it1 = find(AdjList[key1].begin(), AdjList[key1].end(), key2);
            if (it1 != AdjList[key1].end()) {
                AdjList[key1].erase(it1);
            }

            // Find the iterator that points to key2 in the adjacency list of key1
            auto it2 = find(AdjList[key2].begin(), AdjList[key2].end(), key1);
            if (it2 != AdjList[key2].end()) {
                AdjList[key2].erase(it2);
            }
        }

        int getEdges(){
            return this->NumE;
        }

        int getVertices(){
            return this->NumV;
        } 
};

#endif