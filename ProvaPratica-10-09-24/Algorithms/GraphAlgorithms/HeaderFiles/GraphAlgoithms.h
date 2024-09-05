#ifndef _GRAPH_ALGORITHMS_
#define _GRAPH_ALGORITHMS_

#include "../../../DataStructures/Graph/HeaderFiles/Graph.h"
#include "../../../DataStructures/Heap/HeaderFiles/Heap.h"
#include <queue>
#include <stack>
#include <unordered_set>

template<typename T, typename GraphType>
class GraphAlgorithms {
public:

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
