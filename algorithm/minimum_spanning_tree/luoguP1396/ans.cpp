#include <iostream>
#include <vector>
#include <algorithm>

#define N_MAX 10005
#define INF 0x3f3f3f3f

using namespace std;

int m, n, s, t;

class Edge {
public:
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator< (const Edge& e) {
        return w < e.w;
    }
};

int fa[N_MAX];

int find(int t) {
    if (fa[t] != t) fa[t] = find(fa[t]);
    return fa[t];
}

void join(int a, int b) {
    fa[find(a)] = find(b);
}

vector<Edge> edges;

void input() {
    cin >> n >> m >> s >> t;
    // cout << m << endl;
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v, w));
    }
}

int main() {
    input();

    sort(edges.begin(), edges.end());
    for (int i = 0; i <= n; i ++) {
        fa[i] = i;
    }

    int maxW = 0;

    for (Edge e : edges) {
        if (find(s) == find(t)) break;
        maxW = max(e.w, maxW);
        join(e.u, e.v);
    }

    cout << maxW << endl;

    return 0;
}