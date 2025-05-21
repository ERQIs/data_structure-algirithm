#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

#define N_MAX 2002
#define INFI 0x3f3f3f3f

using namespace std;

int n, m;

typedef pair<int, int> PII;

vector<PII> graph[N_MAX];

long long dis[N_MAX];
int cnt[N_MAX];
bool inQueue[N_MAX];

void set_init_input() {
    cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));
    memset(inQueue, false, sizeof(inQueue));
    for (int i = 0; i < n; i ++) {
        graph[i] = vector<PII>();
    }
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w >= 0) {
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        } else {
            graph[u].push_back({v, w});
        }
    }
}

bool neg_circuit() {
    queue<int> q;
    q.push(1); inQueue[1] = true;
    dis[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inQueue[u] = false;

        for (auto [v, w] : graph[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] > n) {
                    return true;
                }
                if (!inQueue[v]) {
                    q.push(v); inQueue[v] = true;
                }
            }
        }
    }
    return false;
}

int main()
{
    int t;
    cin >> t;
    while (t --) {
        set_init_input();
        cout << (neg_circuit() ? "YES" : "NO") << endl;
    }
    return 0;
}