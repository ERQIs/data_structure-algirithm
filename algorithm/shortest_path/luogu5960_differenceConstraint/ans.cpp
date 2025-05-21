#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

#define INFI 0x3f3f3f3f
#define N_MAX 5005

using namespace std;

int dis[N_MAX];
int cnt[N_MAX];
bool inQueue[N_MAX];

typedef pair<int, int> PII;
vector<PII> graph[N_MAX];

int n, m;

bool spfa(int s) {
    queue<int> q;
    q.push(s); inQueue[s] = true;
    dis[s] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        inQueue[u] = false;

        for (auto [v, w] : graph[u]) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                if (cnt[v] ++ > n) {
                    // negative circuit means unsatisfiable
                    return false;
                }
                if (!inQueue[v]) {
                    q.push(v); 
                    inQueue[v] = true;
                }
            }
        }
    }

    return true;
}

int main() {
    memset(dis, 0x3f, sizeof(dis));
    cin >> n >> m;

    for (int i = 0; i < m; i ++) {
        int v, u, w;
        cin >> v >> u >> w;
        graph[u].push_back({v, w});
    }

    for (int i = 1; i <= n; i ++) {
        graph[0].push_back({i, 0});
    }

    if (spfa(0)) {
        for (int i = 1; i <= n; i ++) {
            cout << dis[i] << " \n"[i == n];
        }
    } else {
        cout << "NO" << endl;
    }
    return 0;
}