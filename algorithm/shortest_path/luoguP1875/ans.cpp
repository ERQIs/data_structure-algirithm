#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <cstring>

#define N_MAX 1003
#define START 1002
#define INFI 0x3f3f3f3f

using namespace std;

int graph[N_MAX][N_MAX];
long long dis[N_MAX];
long long cnt[N_MAX];
// bool vis[N_MAX];
int n;

typedef pair<long long, int> PLLI;

void dijkstra(int s) {
    dis[s] = 0;
    cnt[s] = 1;
    priority_queue<PLLI, vector<PLLI>, greater<PLLI>> pq;  // dis, node
    pq.push({0, s});

    while (!pq.empty()) {
        // long long, int
        auto [cost, u] = pq.top(); pq.pop();

        for (int v = 0; v < n; v ++) {
            int w = graph[u][v];
            if (w == INFI) continue;
            if (cost + w < dis[v]) {
                dis[v] = cost + w;
                cnt[v] = cnt[u];
                pq.push({dis[v], v});
            } else if (cost + w == dis[v]) {
                // if (v == 2) {cout << "flag\n";}
                cnt[v] += cnt[u];
            }
        }
    }
}

int main() {
    cin >> n;
    memset(graph, 0x3f, sizeof(graph));
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 0; i < n; i ++) {
        cin >> graph[START][i];
        cnt[i] = 1;
    }
    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c) != EOF) {
        graph[a][c] = graph[START][b];
        graph[b][c] = graph[START][a];
    }
    dijkstra(START);

    cout << dis[0] << " " << cnt[0] << endl;

    // for (int i = 0; i < n; i ++) {
    //     for (int j = 0; j < n; j ++) {
    //         cout << graph[i][j] << " \n"[j == n - 1];
    //     }
    // }
    return 0;
}