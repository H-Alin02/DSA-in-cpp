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

   
    static vector<T> DFS(const GraphType& graph, T start) {
        vector<T> result;
        unordered_set<T> visited;
        DFS_Visit(graph, start, visited, result);
        return result;
    }

    
    static vector<T> BFS(const GraphType& graph, T start) {
        vector<T> result;
        unordered_set<T> visited;
        queue<T> toVisit;

        visited.insert(start);
        toVisit.push(start);

        while (!toVisit.empty()) {
            T currentNode = toVisit.front();
            toVisit.pop();
            result.push_back(currentNode);

            vector<T> neighbours = graph.Neighbours(currentNode);
            for (T neighbour : neighbours) {
                if (visited.find(neighbour) == visited.end()) {
                    visited.insert(neighbour);
                    toVisit.push(neighbour);
                }
            }
        }

        return result;
    }
};


#endif
