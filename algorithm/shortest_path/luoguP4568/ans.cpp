#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <tuple>

#define K_MAX 11
#define N_MAX 10004
#define INFI 0x3f3f3f3f

using namespace std;

typedef pair<int, int> PII;
typedef tuple<int, int, int> TIII;


int n, m, k, s, t;


vector<PII> adj[N_MAX]; // u -> [(v, w)]
int vis[N_MAX][K_MAX];
int dis[N_MAX][K_MAX];

void init_input() {
    cin >> n >> m >> k;
    cin >> s >> t;
    for (int i = 0; i < m; i ++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    memset(dis, 0x3f, sizeof(dis));
}

int main() {
    init_input();

    priority_queue<TIII, vector<TIII>, greater<TIII>> pq; // cost_city_used
    pq.push({0, s, 0});


    while (!pq.empty()) {
        auto [cost, city, used] = pq.top(); pq.pop();
        if (vis[city][used]) continue;
        vis[city][used] = true;

        for (auto [v, w] : adj[city]) {
            if (used < k && dis[v][used + 1] > cost) {
                dis[v][used + 1] = cost;
                pq.push({cost, v, used + 1});
            }

            if (dis[v][used] > cost + w) {
                dis[v][used] = cost + w;
                pq.push(make_tuple(cost + w, v, used));
            }
        }
    }

    int ret = INFI;

    for (int c : dis[t]) {
        if (ret > c) ret = c;
    }

    cout << ret << endl;

    return 0;
}