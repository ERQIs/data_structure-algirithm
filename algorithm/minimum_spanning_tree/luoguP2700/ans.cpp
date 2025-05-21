#include <iostream>
#include <vector>
#include <algorithm>

#define N_MAX 100005
#define K_MAX 100005

using namespace std;
class Edge {
public:
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const Edge& e) {
        return w >= e.w;
    } 
};

bool marked[N_MAX];
int fa[N_MAX];
int n, k;
unsigned long long totalW;
vector<Edge> edges;

int find(int t) {
    if (fa[t] != t) fa[t] = find(fa[t]);
    return fa[t];
}
bool join(int a, int b) {
    int a_set = find(a), b_set = find(b);
    if (marked[a_set] && marked[b_set]) {
        return false;
    }
    if (marked[a_set] || marked[b_set]) {
        marked[a_set] = marked[b_set] = true;
    }
    fa[a_set] = b_set;
    return true;
}

void input_init() {
    for (int i = 0; i < N_MAX; i ++) {
        fa[i] = i;
    }
    cin >> n >> k;
    for (int i = 0; i < k; i ++) {
        int enemy;
        cin >> enemy;
        marked[enemy] = true;
    }
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u, v ,w));
        totalW += w;
    }
    sort(edges.begin(), edges.end());
}


int main() {
    input_init();
    int pickedW = 0;
    int cnt = n;
    for (Edge e : edges) {
        /*
        we don't have to check if e.v and e.u is in same set
        since input graph is a tree
        */
        if (!join(e.v, e.u)) {
            pickedW += e.w;
        }
    }
    cout << pickedW << endl;
    return 0;
}