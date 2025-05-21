#include <iostream>
#include <vector>
#include <algorithm>

#define N_MAX 1003
#define M_MAX 10004

using namespace std;

struct Edge {
public:
    int u, v, w;
    Edge (int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator< (const Edge& e) {
        return w < e.w;
    }
};

vector<Edge> edges;

int n, m, k;

int fa[N_MAX];

int find(int t) {
    if (fa[t] != t) fa[t] = find(fa[t]);
    return fa[t];
}

void join(int a, int b) {
    fa[find(a)] = find(b);
}

void input() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v, w));
    }
}

int main() {
    for (int i = 0; i < N_MAX; i ++) {
        fa[i] = i;
    }

    input();

    sort(edges.begin(), edges.end());

    int cost = 0, cnt = n;
    for (Edge e : edges) {
        if (find(e.v) == find(e.u)) continue;
        join(e.v, e.u);
        cost += e.w;
        
        if (-- cnt == k) break;
    }

    if (cnt == k) {
        cout << cost << endl;
    } else {
        cout << "No Answer" << endl;
    }

    return 0;
}