// Example usage of the Prim's algorithm function

#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

#define N_MAX 5002

#define INF 0x3f3f3f3f

typedef pair<int, int> PII;
vector<PII> adj[N_MAX]; // Adjacency list for the graph
int n, m;
vector<int> dist(N_MAX, INF); // Distance from the source to each vertex
vector<bool> visited(N_MAX, false); // Visited array



void input_graph() {
    cin >> n >> m;
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // For undirected graph
    }
}

int prim_algorithm(int start) {
    dist[start] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> pq; // {weight, node}

    pq.push({0, start});
    int count = 0, total_weight = 0;

    while (!pq.empty()) {
        PII iter = pq.top(); pq.pop();
        int w = iter.first, u = iter.second;

        if (visited[u])  continue;
        visited[u] = true;
        total_weight += w;
        count ++;

        // Add all edges from u to the priority queue
        for (PII jter : adj[u]) {
            int v = jter.first, weight = jter.second;
            if (!visited[v] && weight < dist[v]) {
                dist[v] = weight;
                pq.push({weight, v});
            }
        }
    }
    return count == n ? total_weight : INF;
}

int main()
{
    input_graph();
    int ans = prim_algorithm(1);
    if (ans == INF) {
        cout << "orz" << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}