#include <iostream>
#include <queue>
#include <vector>

#define N_MAX 2001
#define INFI 0x3f3f3f3f

using namespace std;

struct city {
    int powerSource;
    long long cost;
    int x;
    int y;
    bool power;
};

long long adj[N_MAX][N_MAX];
int k[N_MAX];
struct city cities[N_MAX];    // city 0 is power station

typedef pair<int, int> PII;  // <cost, city_num>

int n;
long long total_cost;

void init_input() {
    cin >> n;
    cities[0].cost = 0;
    // cities[0].power = true;
    for (int i = 1; i <= n; i ++) {
        cities[i].cost = INFI;
        cities[i].power = false;
    }

    for (int i = 1; i <= n; i ++) {
        int x, y;
        cin >> cities[i].x >> cities[i].y;
    }

    for (int i = 1; i <= n; i ++) {
        cin >> adj[0][i];
    }

    for (int i = 1; i <= n; i ++) {
        cin >> k[i];
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j < i; j ++) {
            long long dist = abs(cities[i].x - cities[j].x) + abs(cities[i].y - cities[j].y);
            adj[i][j] = dist * (k[i] + k[j]);
            adj[j][i] = adj[i][j];
        }
    }
}

void output() {
    cout << total_cost << endl;
    int v = 0;
    vector<int> stations;
    vector<PII> pairs;
    for (int i = 1; i <= n; i ++) {
        if (cities[i].powerSource == 0) {
            v ++;
            stations.push_back(i);
        } else {
            pairs.push_back({i, cities[i].powerSource});
        }
    }
    cout << v << endl; 
    for (int s : stations) cout << s << " ";
    cout << endl;
    cout << n - v << endl;
    for (PII iter : pairs) {
        cout << iter.first << " " << iter.second  << endl;
    }
    cout << endl;
}



int main()
{
    init_input();

    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        PII cost_city = pq.top(); pq.pop();
        int city_i = cost_city.second;
        int cost = cost_city.first;
        if (cities[city_i].power == true) {
            continue;
        }
        total_cost += cost;

        cities[city_i].power = true;

        for (int i = 1; i <= n; i ++) {
            if (!cities[i].power && cities[i].cost > adj[city_i][i]) {
                cities[i].cost = adj[city_i][i];
                cities[i].powerSource = city_i;
                pq.push({adj[city_i][i], i});
            }
        }
    }

    output();
    return 0;
}