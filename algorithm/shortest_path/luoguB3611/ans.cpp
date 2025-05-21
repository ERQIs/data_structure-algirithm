#include <iostream>
#define N_MAX 102

using namespace std;

bool graph[N_MAX][N_MAX];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            int b;
            cin >> b;
            graph[i][j] = (b == 1);
        }
    }

    for (int k = 0; k < n; k ++) {
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                if (graph[i][k] && graph[k][j]) {
                    graph[i][j] = true;
                }
            }
        }
    } 

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            cout << (graph[i][j] ? "1 " : "0 ");
        }
        cout << endl;
    }

    return 0;
}