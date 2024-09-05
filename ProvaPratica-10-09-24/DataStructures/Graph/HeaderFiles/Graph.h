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


template<typename T, typename Derived> // Pattern CRTP
class Graph{
    protected:
        int NumV;
        int NumE;
        bool directed;

    public:
        Graph(int v, int e, bool directed) : NumV(v), NumE(e), directed(directed) {}

        virtual ~Graph() = default;

        virtual bool adjacent(T key1, T key2) const = 0;
        virtual void insert(T key1, T key2) = 0;
        virtual void print() const = 0;
        virtual vector<T> Neighbours(T key) const = 0;
        virtual int degree(T key) const = 0;
        virtual void deleteEdge(T key1, T key2) = 0;

        int getEdges() const { return this->NumE; }
        int getVertices() const { return this->NumV; }
        bool getDirected() const { return this->directed; }

        // Common methods for obtaining the reverse graph
        Derived reverseGraph() const {
            Derived reverse(NumV, this->directed);
            for(int i = 0; i < this->NumV; ++i){
                vector<T> neighbours = this->Neighbours(i);
                for(T neighbour : neighbours){
                    reverse.insert(neighbour, i);
                }
            }
            return reverse;
        }

};

template<typename T>
class AdjMatGraph : public Graph<T, AdjMatGraph<T>>{

    protected:
        vector<vector<double>> AdjMat;

    public:

        // Create graph with v verticies and 0 edges
        AdjMatGraph(int v, bool directed) : Graph<T, AdjMatGraph<T>>(v,0, directed), AdjMat(v, vector<double>(v, 0)) { }

        // Create graph with information from file
        AdjMatGraph(string path, bool directed): Graph<T, AdjMatGraph<T>>(0,0, directed){
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
            AdjMat.assign(v, vector<double>(v, 0));

            // Add edges
            T x, y;
            for(int i = 0; i < e; ++i){
                infile >> x >> y;
                insert(x, y);
            }

            infile.close();
        }

        AdjMatGraph(int v, int e, bool directed) : Graph<T, AdjMatGraph<T>>(v,0,directed), AdjMat(v, vector<int>(v, 0)){
            random_device rd; 
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, v-1);

            for(int i = 0; i < e; ++i){
                int x = dis(gen);
                int y = dis(gen);
                if(!adjacent(x, y))
                insert(x, y);
            }
        }

        ~AdjMatGraph(){}


        bool adjacent(T key1, T key2) const override{
            return AdjMat[key1][key2];
        }

        void insert(T key1, T key2) override{
            if (!adjacent(key1, key2)) {
            AdjMat[key1][key2] = 1;
            if (!this->directed) {
                AdjMat[key2][key1] = 1;
            }
            this->NumE++;
        }
        }

        void insert(const vector<pair<T,T>>& edges){
            for(auto& edge : edges){
                insert(edge.first, edge.second);
            }
        }

        void print() const override{
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
                for (double value : AdjMat[i]) {
                    cout << value << " ";
                }
                cout << endl;
            }

            cout << "\n";
        }

        vector<T> Neighbours(T key) const override{
            vector<T> neighbours;
            for(int i = 0; i < this->NumV; ++i){
                if(AdjMat[key][i]){
                    neighbours.push_back(i);
                }
            }
            return neighbours;
        }

        int degree(T key) const override{
            return Neighbours(key).size();
        }

        void deleteEdge(T key1, T key2) override {
            if (adjacent(key1, key2)) {
            AdjMat[key1][key2] = 0;
            if (!this->directed) {
                AdjMat[key2][key1] = 0;
            }
            this->NumE--;
            }
        }
};

template<typename T>
class AdjListGraph : public Graph<T, AdjListGraph<T>>{
    
    private:
        vector<list<T>> AdjList;

    public:

        // Create graph with v verticies and 0 edges
        AdjListGraph(int v, bool directed) : Graph<T, AdjListGraph<T>>(v,0, directed), AdjList(v){}

        // Create graph with information from file
        AdjListGraph(string path, bool directed): Graph<T, AdjListGraph<T>>(0,0, directed){
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
            AdjList.assign(v, list<T>());

            // Add edges
            T x, y;
            for(int i = 0; i < e; ++i){
                infile >> x >> y;
                insert(x, y);
            }

            infile.close();
        }

        template<typename Derived>
        AdjListGraph(Graph<T, Derived>& g) : 
        Graph<T, AdjListGraph<T>>(g.getVertices(), g.getEdges(), g.getDirected()), 
        AdjList(g.getVertices()) {
            for(int i = 0; i < this->NumV; i++){
                vector<T> n = g.Neighbours(i);
                for(int j = 0; j < n.size(); j++){
                    if(!adjacent(i,n[j]))
                        insert(i,n[j]);
                }
            }
        }

        ~AdjListGraph(){}

        bool adjacent(T key1, T key2) const override{
            return find(AdjList[key1].begin(), AdjList[key1].end(), key2) != AdjList[key1].end();
        }

        void insert(T key1, T key2) override{
            if (!adjacent(key1, key2)) {
            AdjList[key1].push_back(key2);
            if (!this->directed) {
                AdjList[key2].push_back(key1);
            }
            this->NumE++;
        }
        }

        void insert( const vector<pair<T,T>>& edges){
            for(auto& edge : edges){
                insert(edge.first, edge.second);
            }
        }

        void print() const override{
            for (int i = 0; i < AdjList.size(); ++i) {
                cout <<"[" << i <<"]" << "-->";
                for (T value : AdjList[i]) {
                    cout <<"[" << value <<"]" " ";
                }
                cout << endl;
            }

            cout << "\n";
        }

        vector<T> Neighbours(T key) const override{
            vector<T> neighbours(AdjList[key].begin(), AdjList[key].end());
            return neighbours;
        }

        int degree(T key) const override{
            return Neighbours(key).size();
        }

        void deleteEdge(T key1, T key2) override{
            auto it1 = find(AdjList[key1].begin(), AdjList[key1].end(), key2);
            if (it1 != AdjList[key1].end()) {
                AdjList[key1].erase(it1);
                this->NumE--;
            }   

            if (!this->directed) {
                auto it2 = find(AdjList[key2].begin(), AdjList[key2].end(), key1);
                if (it2 != AdjList[key2].end()) {
                    AdjList[key2].erase(it2);
                }
            }
        }
};

#endif