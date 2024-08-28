#ifndef _GRAPH_ALGORITHMS_
#define _GRAPH_ALGORITHMS_

#include "../../../DataStructures/Graph/HeaderFiles/Graph.h"
#include <queue>
#include <stack>
#include <unordered_set>

template<typename T, typename GraphType>
class GraphAlgorithms {
public:

    // Implementazione ricorsiva della DFS (Depth-First Search)
    static void DFS_Visit(const GraphType& graph, T node, unordered_set<T>& visited, vector<T>& result) {
        visited.insert(node);
        result.push_back(node);
    
        vector<T> neighbours = graph.Neighbours(node);
        for (T neighbour : neighbours) {
            if (visited.find(neighbour) == visited.end()) {
                DFS_Visit(graph, neighbour, visited, result);
            }
        }
    }

    static void DFS_Visit(const GraphType& graph, T node, unordered_set<T>& visited, stack<T>& result) {
        vector<T> neighbours = graph.Neighbours(node);
        for (T neighbour : neighbours) {
            if (visited.find(neighbour) == visited.end()) {
                DFS_Visit(graph, neighbour, visited, result);
            }
        }
        visited.insert(node);
        result.push(node);
    }

    // DFS per esplorare tutte le componenti connesse
    static unordered_map<int, vector<T>> DFS(const GraphType& graph) {
        unordered_map<int, vector<T>> components; // Mappa che memorizza le componenti
        unordered_set<T> visited;
        int componentIndex = 0;

        for (int i = 0; i < graph.getVertices(); ++i) {
            if (visited.find(i) == visited.end()) { // Nodo non ancora visitato
                vector<T> component;
                DFS_Visit(graph, i, visited, component);
                components[componentIndex++] = component;
            }
        }

        return components;
    }

    // BFS per esplorare tutte le componenti connesse
    static unordered_map<int, vector<T>> BFS(const GraphType& graph) {
        unordered_map<int, vector<T>> components; // Mappa che memorizza le componenti
        unordered_set<T> visited;
        int componentIndex = 0;

        for (int i = 0; i < graph.getVertices(); ++i) {
            if (visited.find(i) == visited.end()) { // Nodo non ancora visitato
                vector<T> component;
                queue<T> toVisit;

                visited.insert(i);
                toVisit.push(i);

                while (!toVisit.empty()) {
                    T currentNode = toVisit.front();
                    toVisit.pop();
                    component.push_back(currentNode);

                    vector<T> neighbours = graph.Neighbours(currentNode);
                    for (T neighbour : neighbours) {
                        if (visited.find(neighbour) == visited.end()) {
                            visited.insert(neighbour);
                            toVisit.push(neighbour);
                        }
                    }
                }

                components[componentIndex++] = component;
            }
        }

        return components;
    }
    

    //Reverse postorder Topological Sort
    static stack<T> ReversePostTopologicalSort(const GraphType& graph) {
        stack<T> result;
        unordered_set<T> visited;

        for (int i = 0; i < graph.getVertices(); ++i) {
            if (visited.find(i) == visited.end()) { // Nodo non ancora visitato
                DFS_Visit(graph, i, visited, result);
            }
        }
        
        return result;
    }


    static vector<int> KahnTopologicalSort(const GraphType& graph) {
        int NumV = graph.getVertices();

        // Vector to store indegree of each vertex
        vector<int> indegree(NumV);
        for (int i = 0; i < NumV ; i++) {
            for (auto it : graph.Neighbours(i)) {
                indegree[it]++;
            }
        }

        // Queue to store vertices with indegree 0
        queue<int> queue;
        for (int i = 0; i < NumV; i++) {
            if (indegree[i] == 0) {
                queue.push(i);
            }
        }

        vector<int> result;
        while (!queue.empty()) {
            int node = queue.front();
            queue.pop();
            result.push_back(node);

            // Decrease indegree of adjacent vertices as the
            // current node is in topological order
            for (auto it : graph.Neighbours(node)) {
                indegree[it]--;

                // If indegree becomes 0, push it to the queue
                if (indegree[it] == 0)
                    queue.push(it);
            }
        }

        // Check for cycle
        if (result.size() != NumV) {
            cout << "Graph contains cycle!" << endl;
            return {};
        }

        return result;
    }
};


#endif
