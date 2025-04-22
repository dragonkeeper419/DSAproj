#include <iostream>
#include <queue>
#include <vector>

class HopcroftKarp
{
private:
    int m, n; // Number of vertices in left and right columns
    std::vector<std::vector<int> > adj; // Adjacency list, 1-indexed
    std::vector<int> pairU, pairV, dist; // Pairing and distances

    bool bfs()
    {
        std::queue<int> q;


        for (int u = 1; u <= m; u++)
        {
            if (pairU[u] == 0)
            {
                dist[u] = 0;
                q.push(u);
            } else
            {
                dist[u] = INT_MAX;
            }
        }
        dist[0] = INT_MAX;

        while (q.size() > 0)
        {
            int u = q.front();
            q.pop();

            if (dist[u] < dist[0])
            {
                for (int v: adj[u])
                {
                    if (dist[pairV[v]] == INT_MAX)
                    {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        std::cout << "finished bfs : " << (dist[0] != INT_MAX) << std::endl;
        return dist[0] != INT_MAX;
    }

    bool dfs(int u)
    {
        if (u == 0) return true;

        for (int v : adj[u])
        {
            // int v = *i;
            // if (pairV[v] == 0)
            // {
            //     pairV[v] = u;
            //     pairU[u] = v;
            //     return true;
            // }

            if (dist[pairV[v]] == dist[u] + 1)
            {
                if (dfs(pairV[v]))
                {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INT_MAX;
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
        while (bfs())
        {
            for (int u = 1; u <= m; u++)
            {
                if (pairU[u] == 0 && dfs(u))
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
