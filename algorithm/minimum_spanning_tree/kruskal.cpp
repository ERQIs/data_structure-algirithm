// Example usage of kruskal's algorithm function

#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_N 5005
#define INF 0x3f3f3f3f

using namespace std;

class Edge {
public:
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const Edge &e) {
        return w < e.w;
    }
};

int fa[MAX_N];  // Union-Find array

int find(int t) {
    if (fa[t] != t) fa[t] = find(fa[t]);
    return fa[t];
}

void union_sets(int u, int v) {
    fa[find(u)] = find(v);
}

vector<Edge> edges;
int n, m;

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v, w));
    }
}

int kruskal_algorithm() {
    for (int i = 0; i < MAX_N; i ++) {
        fa[i] = i;
    }
    sort(edges.begin(), edges.end());
    int cnt = 0;
    int total_weight = 0;

    for (Edge e : edges) {
        if (find(e.u) == find(e.v)) {
            continue;
        }
        cnt ++;
        total_weight += e.w;
        union_sets(e.u, e.v);
        if (cnt == n - 1) {
            break;
        }
    }
    return cnt == n - 1 ? total_weight : INF;
}

int main()
{
    input();
    int ans = kruskal_algorithm();
    if (ans == INF) {
        cout << "orz" << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}