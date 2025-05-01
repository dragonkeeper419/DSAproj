#include <iostream>
#include <queue>
#include <vector>

class HopcroftKarp
{
private:
    int m, n; // Number of vertices in left and right columns
    std::vector<std::vector<int> > adj; // Adjacency list, 1-indexed
    std::vector<int> pairU, pairV, dist; // Pairing and distances, 1-indexed

    bool bfs() // Breadth-First Search
    {
        std::queue<int> q;


        for (int u = 1; u <= m; u++) // Iterates over all verticies in U/left column
        {
            if (pairU[u] == 0) // If u has no pairing
            {
                dist[u] = 0; // Set distance to 0
                q.push(u); // Add u to the queue
            } else
            {
                dist[u] = INT_MAX; // Set distance to infinity
            }
        }
        dist[0] = INT_MAX; // Set distance to the dummy node to infinity

        while (q.size() > 0) // While queue is not empty
        {
            int u = q.front(); // Get the front element
            q.pop();

            if (dist[u] < dist[0]) // If distance the distance of u is less than the current shortest augmenting path
            {
                for (int v: adj[u]) // for each vertex v in the adjacency list of u
                {
                    if (dist[pairV[v]] == INT_MAX) // If the node v is matched to has not been visited
                    {
                        dist[pairV[v]] = dist[u] + 1; // set the distance to the node v is matched to, to the distance of u, plus 1
                        q.push(pairV[v]); // add the node v is matched to, to the queue
                    }
                }
            }
        }
        return dist[0] != INT_MAX; // If the distance of the dummy node is not infinity, then there is an augmenting path, otherwise it is maximal
    }

    bool dfs(int u) // Depth-First Search
    {
        if (u == 0) return true; // If u is the dummy node, return true

        for (int v : adj[u]) // for each vertex v in the adjacency list of u
        {
            if (dist[pairV[v]] == dist[u] + 1) // If the distance of the node v is matched to is equal to the distance of u, plus 1
            {
                if (dfs(pairV[v])) // recursive, if the node v is matched to can be matched to another node
                {
                    pairV[v] = u; // set the node v is matched to, to u
                    pairU[u] = v; // set the node u is matched to, to v
                    return true;
                }
            }
        }
        dist[u] = INT_MAX; // if no augmenting path is found, set the distance of u to infinity
        return false;
    }

public:
    HopcroftKarp(int m, int n)
    {
        this->m = m;
        this->n = n;
        adj.resize(m + 1);
        pairU.resize(m + 1, 0);
        pairV.resize(n + 1, 0);
        dist.resize(m + 1, 0);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    int maxMatching()
    {
        int matching = 0;
        while (bfs()) // While there is at least one augmenting path
        {
            for (int u = 1; u <= m; u++) // Iterate over all vertices in U/left column
            {
                if (pairU[u] == 0 && dfs(u)) // If u has no pairing and there is an augmenting path
                {
                    matching++;
                }
            }
        }
        return matching;
    }

    std::vector<std::pair<int, int>> getMatches()
    {
        std::vector<std::pair<int, int>> matches;
        for (int u = 1; u <= m; u++)
        {
            if (pairU[u] != 0)
            {
                matches.emplace_back(u, pairU[u]);
            }
        }
        return matches;
    }

    bool isMatched(int u)
    {
        return pairU[u] != 0;
    }

    int getMatch(int u)
    {
        return pairU[u];
    }
};

void printMST(std::vector<int> &parent, std::vector<std::vector<int>> &graph) {
    std::cout << "Edge \tWeight\n";
    for (int i = 1; i < graph.size(); i++)
        std::cout << parent[i] << " - " << i << " \t"
             << graph[parent[i]][i] << " \n";
}

int minKey(std::vector<int> &key, std::vector<bool> &mstSet) {
    int min = INT_MAX, min_index; // Initialize min value

    for (int v = 0; v < mstSet.size(); v++)
        if (!mstSet[v] && key[v] < min) { // If the node has not been visited and the edge weight is less than the current min
            min = key[v], min_index = v;
        }
    return min_index;
}

void prim_algo(std::vector<std::vector<int>> &graph) {
    int vertex_count = graph.size();
    std::vector<int> MST(vertex_count); // Contains the MST branches
    std::vector<int> node_query(vertex_count); // Contains the nodes connect to those in the MST
    std::vector<bool> visted(vertex_count); // Tracks what nodes have been visited
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

int main()
{
    std::cout << "Part 1: Hopcroft-Karp" << std::endl;

    HopcroftKarp graph(5, 5);
    graph.addEdge(1, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 1);
    graph.addEdge(2, 5);
    graph.addEdge(3, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 1);
    graph.addEdge(4, 5);
    graph.addEdge(5, 2);
    graph.addEdge(5, 4);

    int max_matching = graph.maxMatching();
    std::cout << max_matching << std::endl;

    auto matches = graph.getMatches();
    for (const auto& match : matches)
    {
        std::cout << match.first << " " << match.second << std::endl;
    }


    // Initializing the graph with edge weights
    std::vector<std::vector<int>> graph_matrix = { { 0, 15,  0,  6,  0,  1 },
                                  {15,  0, 13,  8,  0, 15 },
                                  { 0, 13,  0, 21, 12,  7 },
                                  { 6,  8, 21,  0,  9,  3 },
                                  { 0,  0, 12,  9,  0,  9 },
                                  { 1, 15,  7,  3,  9,  0 } };

    std::cout << "Part 2: Prim's Algorithm" << std::endl;
    prim_algo(graph_matrix);

    return 0;
}
