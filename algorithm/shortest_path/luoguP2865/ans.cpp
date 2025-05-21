#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define N_MAX 5005
#define INFI 0x3f3f3f3f

using namespace std;

long long dis1[N_MAX];
long long dis0[N_MAX];
bool vis[N_MAX];

typedef pair<int, int> PII;
vector<PII> graph[N_MAX]; // v w

int n, r;

void dijkstra() {
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    // dis0, node
    pq.push({0, 1});
    dis0[1] = 0;
    while (!pq.empty()) {
        auto [dis, node] = pq.top(); pq.pop();

        // cannot use vis to cut, because that will cut away
        // some second-shortest path

        for (auto [v, w] : graph[node]) {
            int new_dis = dis + w;
            if (dis0[v] > new_dis) {
                // cout << "flag" << endl;
                dis1[v] = dis0[v];
                dis0[v] = new_dis;
                pq.push({new_dis, v});
            } else if (dis0[v] < new_dis && new_dis < dis1[v]) {
                // second-shortest path might be calculated from second-shortest + w
                dis1[v] = new_dis;
                // we must push this so we don't miss any second-shortest
                pq.push({new_dis, v});
                
            }
        }
    }
}

int main() {

    cin >> n >> r;
    for (int i = 0; i < r; i ++) {
        int a, b, d;
        cin >> a >> b >> d;
        graph[a].push_back({b, d});
        graph[b].push_back({a, d});
    }

    memset(dis0, 0x3f, sizeof(dis1));
    memset(dis1, 0x3f, sizeof(dis0));

    dijkstra();

    cout << dis1[n] << endl;
    
    return 0;
}