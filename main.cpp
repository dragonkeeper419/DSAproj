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

int main()
{
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

    return 0;
}
