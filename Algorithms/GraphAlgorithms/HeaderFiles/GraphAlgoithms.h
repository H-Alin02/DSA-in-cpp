#ifndef _GRAPH_ALGORITHMS_
#define _GRAPH_ALGORITHMS_

#include "../../../DataStructures/Graph/HeaderFiles/Graph.h"
#include "../../../DataStructures/UnionFind/HeaderFiles/UnionFind.h"
#include "../../../DataStructures/Heap/HeaderFiles/Heap.h"
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

    static pair<vector<pair<pair<T,T>,double>>, double> KruskalMST(const GraphType& graph) {
        vector<pair<pair<T, T>, double>> result;
        vector<pair<pair<T, T>, double>> edges = graph.getEdges();
        double MSTCost = 0.0;

        // Sort the edges in increasing order of weight
        sort(edges.begin(), edges.end(), [](const pair<pair<T, T>, double>& a, const pair<pair<T, T>, double>& b) {
            return a.second < b.second;
        });

        UnionFind<int> UF(graph.getVertices());

        for (auto& edge : edges) {
            T u = edge.first.first;
            T v = edge.first.second;
            double weight = edge.second;

            if (!UF.connect(u, v)) {
                result.push_back({{u, v}, weight});
                UF.UnionBySize(u, v);
                MSTCost += weight;
            }

            // Stop when all vertices are connected
            if (result.size() == graph.getVertices() - 1) {
                break;
            }
        }

        return {result,MSTCost};
    }

    static pair<vector<pair<pair<T, T>, double>>, double> LazyPrimMST(const GraphType& graph) {
        vector<pair<pair<T, T>, double>> result;
        int V = graph.getVertices();

        vector<bool> visited(V,false);

        Heap<pair<pair<T, T>, double>> minHeap([](const pair<pair<T,T>,double>& a, const pair<pair<T,T>,double>& b) {
            return a.second < b.second;
        }, true);

        double MSTCost = 0.0;

        // LAMBDA FUNCTION TO ADD NEIGHBOURS TO THE MST
        // starts from node
        // Mark node as visited
        // For each neighbour of node
        // If the neighbour is not visited
        // Add the edge to the minHeap
        auto addEdges = [&](int node) {
            visited[node] = true;
            for (const auto& edge : graph.getEdges(node)) {
                int u = edge.first.first;
                int v = edge.first.second;
                double weight = edge.second;

                if (u == node && !visited[v]) {
                    minHeap.push({{u, v}, weight});
                } else if (v == node && !visited[u]) {
                    minHeap.push({{v, u}, weight});
                }
            }
        };

        addEdges(0); // Starts from node 0

        while (!minHeap.empty() && result.size() < V - 1) {
            auto edge = minHeap.top();
            minHeap.pop();
            int u = edge.first.first;
            int v = edge.first.second;
            double weight = edge.second;

            if (visited[v]) continue; // Goes to the next iteration

            result.push_back({{u, v}, weight});
            MSTCost += weight;

            addEdges(v); // Aggiungi i nuovi bordi del nodo v all'MST
        }

        return {result, MSTCost};
    }

    static pair<vector<pair<pair<T, T>, double>>, double> EagerPrimMST(const GraphType& graph) {
        vector<pair<pair<T, T>, double>> result;
        int V = graph.getVertices();

        vector<bool> visited(V,false);

        Heap<pair<pair<T, T>, double>> minHeap([](const pair<pair<T,T>,double>& a, const pair<pair<T,T>,double>& b) {
            return a.second < b.second;
        }, true);

        double MSTCost = 0.0;

        vector<double> key(V, numeric_limits<double>::infinity()); // Store min weight edge to include in MST
        vector<int> parent(V, -1);  // Store parent of node in MST

        key[0] = 0.0; // Start from the first node, weight 0
        minHeap.push({{0,0},0}); // Node 0 with key value 0

        while (!minHeap.empty() && result.size() < V - 1) {
            int u = minHeap.top().first.second;
            minHeap.pop();

            if (visited[u]) continue;

            visited[u] = true; // Include node in MST
            MSTCost += key[u];

            if (parent[u] != -1) {
                result.push_back({{parent[u], u}, key[u]});
            }

            // Update keys and parents for adjacent nodes
            for (const auto& edge : graph.getEdges(u)) {
                int v = edge.first.second;
                double weight = edge.second;

                if (!visited[v] && key[v] > weight) {
                    key[v] = weight;
                    parent[v] = u;
                    minHeap.push({{u,v},weight});
                }
            }
        }

        return {result, MSTCost};

    }

    // This version of dijkstra only returns the shortest distance from source to the destination
    static int dijkstra(int start, int end, const GraphType& graph) {
        int nodes = graph.getVertices();

        if (start < 0 || start >= nodes || end < 0 || end >= nodes) {
            throw out_of_range("Invalid start or end node");
        }

        // Priority queue for choosing the next node with the shortest distance
        // Takes in input, the pair of node and weight
        Heap<pair<T, double>> pq([](const pair<T,double>& a, const pair<T,double>& b) {
            return a.second < b.second;
        }, true);

        // Vector to store the shortest distance from source to each node
        vector<double> dist(nodes, numeric_limits<double>::infinity()); // Inizialize to infinity

        dist[start] = 0; // Distance from start to start is 0
        pq.push({start, 0}); // Insert the start node in PQ

        while (!pq.empty()) {
            int u = pq.top().first; // Select the node with the shortest distance
            int u_dist = pq.top().second; // Weight of the selected node
            pq.pop();

            // If the selected node is the destination, return the weight
            if (u == end)
                return u_dist;

            // Iterate over the neighbors of 'u'
            for (const auto &neighbor : graph.getEdges(u)) {
                int v = neighbor.first.second;
                double weight = neighbor.second;

                // If the weight from 'u' to 'v' is shorter than the current weight, update it
                if (dist[v] > u_dist + weight) {
                    dist[v] = u_dist + weight;
                    pq.push({v,dist[v]});
                }
            }
        }

        // If the destination is not reachable, return -1
        return -1;
    }
};

#endif
