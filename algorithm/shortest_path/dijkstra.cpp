#include <iostream>
#include <queue>
#include <vector>
#define N_MAX 100005
#define INFI 0x3f3f3f3f

using namespace std;

int n, m, s;
typedef pair<int, int> PII;
vector<vector<PII>> adj;

bool vis[N_MAX];
int dis[N_MAX];

void init_input() {
    cin >> n >> m >> s;
    adj = vector<vector<PII>>(n + 1);
    for (int i = 0; i <= n; i ++) {
        dis[i] = INFI;
    }
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
}

int main() {
    init_input();

    priority_queue<PII, vector<PII>, greater<PII>> pq;
    // dis, node
    dis[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        PII dis_node = pq.top(); pq.pop();
        int node_dis = dis_node.first;
        int node = dis_node.second;

        if (vis[node]) continue;
        vis[node] = true;

        for (PII v_w : adj[node]) {
            int v = v_w.first, w = v_w.second;
            if (vis[v]) continue;
            int new_dis = dis[node] + w;
            if (new_dis < dis[v]) {
                dis[v] = new_dis;
                pq.push({new_dis, v});
            }
        }
    }

    for (int i = 1; i <= n; i ++) {
        cout << dis[i] << " ";
    }
    cout << endl;

    return 0;
}