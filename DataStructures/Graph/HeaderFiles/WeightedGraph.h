#ifndef _WEIGHTED_GRAPH_
#define _WEIGHTED_GRAPH_

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <random>
#include "Graph.h"
using namespace std;

template<typename T, typename Derived>
class WeightedGraph : public Graph<T, Derived> {
public:
    WeightedGraph(int v, int e) : Graph<T, Derived>(v, e, false) {}

    virtual ~WeightedGraph() = default;

    virtual bool adjacent(T key1, T key2) const = 0;
    virtual void insert(T key1, T key2, double weight) = 0;
    void insert(T key1, T key2) { insert(key1, key2, 1.0); }
    virtual void print() const = 0;
    virtual vector<T> Neighbours(T key) const = 0;
    virtual int degree(T key) const = 0;
    virtual void deleteEdge(T key1, T key2) = 0;
};

template<typename T>
class AdjMatWeightedGraph : public WeightedGraph<T, AdjMatWeightedGraph<T>>, public AdjMatGraph<T> {
public:
    AdjMatWeightedGraph(int v) : WeightedGraph<T, AdjMatWeightedGraph<T>>(v, 0), AdjMatGraph<T>(v, false) {}

    AdjMatWeightedGraph(string path) : WeightedGraph<T, AdjMatWeightedGraph<T>>(0, 0), AdjMatGraph<T>(0, false){
        ifstream infile(path); 
        if(!infile){
            cerr << "Error opening file" << endl;
            exit(1);
        }

        // Add vertices
        int v, e;
        infile >> v >> e;
        AdjMatGraph<T>::NumV = v;
        AdjMatGraph<T>::NumE = e;
        AdjMatGraph<T>::AdjMat.assign(v, vector<double>(v, 0));

        // Add edges
        T x, y;
        double z;
        for(int i = 0; i < e; ++i){
            infile >> x >> y >> z;
            insert(x, y, z);
        }

        infile.close();
    }

    AdjMatWeightedGraph(int v, int e) : WeightedGraph<T, AdjMatWeightedGraph<T>>(v, 0), AdjMatGraph<T>(v, false) {
        random_device rd; 
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, v-1);
        uniform_int_distribution<> dis2(1,50);

        for(int i = 0; i < e; ++i){
            int x = dis(gen);
            int y = dis(gen);
            int z = dis2(gen);
            if(!adjacent(x, y))
                insert(x, y, z);
        }
    }

    virtual ~AdjMatWeightedGraph() = default;

    bool adjacent(T key1, T key2) const override {
        return AdjMatGraph<T>::adjacent(key1, key2);
    }

    void insert(T key1, T key2, double weight) override {
        // Inserimento di archi pesati
        if (!adjacent(key1, key2)) {
            this->AdjMat[key1][key2] = weight;
            if (!AdjMatGraph<T>::directed) {
                this->AdjMat[key2][key1] = weight;
            }
            AdjMatGraph<T>::NumE++;
        }
    }

    void print() const override {
        AdjMatGraph<T>::print();
    }

    vector<T> Neighbours(T key) const override {
        return AdjMatGraph<T>::Neighbours(key);
    }

    int degree(T key) const override {
        return AdjMatGraph<T>::degree(key);
    }

    void deleteEdge(T key1, T key2) override {
        AdjMatGraph<T>::deleteEdge(key1, key2);
    }

    vector<pair<pair<T, T>, double>> getEdges() const {
        vector<pair<pair<T, T>, double>> edges;
        for (int i = 0; i < this->AdjMat.size(); ++i) {
            // We only consider upper triangular matrices for avoiding duplicates
            for (int j = i + 1; j < this->AdjMat[i].size(); ++j) { 
                if (this->AdjMat[i][j]) {
                    edges.push_back({{i, j}, this->AdjMat[i][j]});
                }
            }
        }
        return edges;
    }

    int getVertices() const { return AdjMatGraph<T>::NumV; }
};

template<typename T>
class AdjListWeightedGraph : public WeightedGraph<T, AdjListWeightedGraph<T>> {
protected:
    vector<list<pair<T, double>>> AdjList;

public:
    AdjListWeightedGraph(int v) : WeightedGraph<T, AdjListWeightedGraph<T>>(v, 0){
        AdjList.resize(v);
    }

    AdjListWeightedGraph(string path) : WeightedGraph<T, AdjListWeightedGraph<T>>(0, 0){
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
            AdjList.assign(v, list<pair<T, double>>());

            // Add edges
            T x, y;
            double z;
            for(int i = 0; i < e; ++i){
                infile >> x >> y >> z;
                insert(x, y, z);
            }

            infile.close();
    }

    virtual ~AdjListWeightedGraph() = default;

    bool adjacent(T key1, T key2) const override {
        for(pair<T, double> value : AdjList[key1]) {
            if(value.first == key2) 
                return true;
        }
        return false;
    }

    void insert(T key1, T key2, double weight) override {
        // Inserimento di archi pesati
        if (!adjacent(key1, key2)) {
            AdjList[key1].push_back({key2, weight});
            AdjList[key2].push_back({key1, weight});
            this->NumE++;
        }
    }

    void print() const override {
        for (int i = 0; i < AdjList.size(); ++i) {
                cout <<"[" << i <<"]" << "-->";
                for (pair<T, double> value : AdjList[i]) {
                    cout <<"[" << value.first << "|"<< value.second <<"]" " ";
                }
                cout << endl;
            }

            cout << "\n";
    }

    vector<T> Neighbours(T key) const {
        vector<T> neighbours;
        for(pair<T, double> value : AdjList[key]) {
            neighbours.push_back(value.first);
        }
        return neighbours;
    }

    int degree(T key) const{
        return Neighbours(key).size();
    }

    void deleteEdge(T key1, T key2) override {
        for(pair<T, double> value : AdjList[key1]) {
            if(value.first == key2) {
                AdjList[key1].remove({key2, value.second});
                this->NumE--;
                break;
            }
        }
    }

    vector<pair<pair<T, T>, double>> getEdges() const {
        vector<pair<pair<T, T>, double>> edges;
        vector<bool> visited(this->AdjList.size(), false);

        for (int i = 0; i < this->AdjList.size(); ++i) {
            for (const auto& neighbor : this->AdjList[i]) {
                T j = neighbor.first;
                double weight = neighbor.second;

                // Ensure each edge is added only once
                if (!visited[j]) {
                    edges.push_back({{i, j}, weight});
                }
            }
            visited[i] = true;
        }
        return edges;
    }

    int getVertices() const { return this->NumV; }
};

#endif
