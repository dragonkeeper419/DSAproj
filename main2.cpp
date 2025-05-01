//
// Created by Ifeatu on 4/22/2025.
//

// Prim's Algorithm in C++

#include <iostream>
#include <vector>

using namespace std;

void printMST(vector<int> &parent, vector<vector<int>> &graph) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < graph.size(); i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[parent[i]][i] << " \n";
}

int minKey(vector<int> &key, vector<bool> &mstSet) {
    int min = INT_MAX, min_index; // Initialize min value

    for (int v = 0; v < mstSet.size(); v++)
        if (!mstSet[v] && key[v] < min) { // If the node has not been visited and the edge weight is less than the current min
            min = key[v], min_index = v;
        }
    return min_index;
}

void prim_algo(std::vector<std::vector<int>> &graph) {
    int vertex_count = graph.size();
    vector<int> MST(vertex_count); // Contains the MST branches
    vector<int> node_query(vertex_count); // Contains the nodes connect to those in the MST
    vector<bool> visted(vertex_count); // Tracks what nodes have been visited
    for (int i = 0; i < vertex_count; i++)
    {
        node_query[i] = INT_MAX; //Setting all nodes as INF far away
        visted[i] = false; //Setting all nodes as unvisited
    }
    node_query[0] = 0; //Setting node 0 to be the first node we look at
    MST[0] = -1; //Setting to node 0 to be the first node of the MST
    for (int count = 0; count < vertex_count - 1; count++) {
        int u = minKey(node_query, visted); //Finding the adjacent node with the least weight
        visted[u] = true; //Setting the node as visited, so we don't look cycle back to it
        for (int v = 0; v < vertex_count; v++)
        {
            if (graph[u][v] && !visted[v] && graph[u][v] < node_query[v]) //If u is connected to v & v jas not been visited & the edge weight connecting u and v is less than INF
            {
               MST[v] = u, node_query[v] = graph[u][v]; //Adds the current node to the MST and adds the nodes connected to it to the query
            }
        }
    }
    printMST(MST, graph);
}

int main() {
    // Initializing the graph with edge weights
    vector<vector<int>> graph = { { 0, 15,  0,  6,  0,  1 },
                                  {15,  0, 13,  8,  0, 15 },
                                  { 0, 13,  0, 21, 12,  7 },
                                  { 6,  8, 21,  0,  9,  3 },
                                  { 0,  0, 12,  9,  0,  9 },
                                  { 1, 15,  7,  3,  9,  0 } };

    // Print the solution
    prim_algo(graph);

    return 0;
}
