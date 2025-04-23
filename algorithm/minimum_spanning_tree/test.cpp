#include <iostream>
#define B_max 502
#define INF 0x3f3f3f3f

#include<queue>

using namespace std;

int G[B_max][B_max];
int a, b;
bool vis[B_max];
int dis[B_max];


int input()
{
    cin >> a >> b;
    cout << a << " " << b << endl;
    for (int i = 0; i < b; i ++) {
        // for (int j = 0; j < b; j ++) {
        //     // cin >> G[i][j];
        //     // if (i != j && G[i][j] == 0) {
        //     //     G[i][j] = a;
        //     // }
        //     cout << i << " " << j << endl;
        // }
        cout << b << endl;
    }
}

int main()
{
    input();
    int total = 0;
    // for (int i = 0; i <= b; i ++) {
    //     dis[i] = INF;
    // }

    dis[0] = a;
    // for (int i = 0; i < b; i ++) {
    //     int min_dist = INF, u = -1;
    //     for (int j = 0; j < b; j ++) {
    //         if (!vis[j] && dis[j] < min_dist) {
    //             min_dist = dis[j];
    //             u = j;
    //         }
    //     }

    //     total += min_dist;
    //     vis[u] = true;

    //     for (int v = 0; v < b; v ++) {
    //         if (!vis[v] && G[u][v] < dis[v]) {
    //             dis[v] = G[u][v];
    //         }
    //     }
    // }
    cout << total << endl;
    return 0;
}