//
// Created by Ifeatu on 4/22/2025.
//

// Prim's Algorithm in C++

#include <cstring>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

#define INF 9999999

void printMST(vector<int> &parent, vector<vector<int>> &graph) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < graph.size(); i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[parent[i]][i] << " \n";
}

int minKey(vector<int> &key, vector<bool> &mstSet) {

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < mstSet.size(); v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void prim_algo(std::vector<std::vector<int>> &graph) {
    int vertex_count = graph.size();

    vector<int> parent(vertex_count);

    vector<int> next_branch(vertex_count);

    vector<bool> visted(vertex_count);

    for (int i = 0; i < vertex_count; i++)
    {
        next_branch[i] = INT_MAX;
        visted[i] = false;
    }

    next_branch[0] = 0;

    parent[0] = -1;

    for (int count = 0; count < vertex_count - 1; count++) {

        int u = minKey(next_branch, visted);

        visted[u] = true;

        for (int v = 0; v < vertex_count; v++)
        {
            if (graph[u][v] && visted[v] == false && graph[u][v] < next_branch[v])
            {
                parent[v] = u, next_branch[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

int main() {
    // Initializing the graph with edge weights
    vector<vector<int>> graph = { { 0, 15,  0,  6, 2,  0 },
                                  { 3,  0,  7,  0, 0,  0 },
                                  { 0, 13,  0, 21, 7, 12 },
                                  { 8,  8,  0,  0, 9,  7 },
                                  { 0, 10, 12,  0, 0,  0 },
                                  { 1, 15,  7,  3, 9,  0 } };

    // Print the solution
    prim_algo(graph);

    return 0;
}
