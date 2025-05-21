#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    priority_queue<int> pq;
    for (int i = 0; i < 5; i ++) {
        pq.push(i);
    }
    priority_queue<int> pq2 = pq;
    while (!pq.empty()) pq.pop();
    cout << pq2.size() << endl;
    return 0;
}