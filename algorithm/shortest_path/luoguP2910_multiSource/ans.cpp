#include <iostream>
#include <vector>
#include <cstring>

#define INFI 0x3f3f3f3f
#define N_MAX 102

using namespace std;

int n, m;
int graph[N_MAX][N_MAX];
// int graph[N_MAX][N_MAX];

void Floyd_Warshall() {
    for (int k = 0; k < n; k ++) {
        for (int u = 0; u < n; u ++) {
            for (int v = 0; v < n; v ++) {
                if (graph[u][v] > graph[u][k] + graph[k][v]) {
                    graph[u][v] = graph[u][k] + graph[k][v];
                }
            }
        }
    }
}

int main() {
    cin >> n >> m;
    vector<int> line;
    for (int i = 0; i < m; i ++) {
        int isl;
        cin >> isl;
        line.push_back(isl - 1);
    }
    for (int u = 0; u < n; u ++) {
        for (int v = 0; v < n; v ++) {
            cin >> graph[u][v];
        }
    }

    Floyd_Warshall();

    int min_danger = 0;
    for (int i = 0; i < m - 1; i ++) {
        min_danger += graph[line[i]][line[i + 1]];
    }
    cout << min_danger << endl;
    return 0;
}