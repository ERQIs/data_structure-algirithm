# P5960 【模板】差分约束

## 题目描述

给出一组包含 $m$ 个不等式，有 $n$ 个未知数的形如：

$$ \begin{cases} x_{c_1}-x_{c'_1}\leq y_1 \\x_{c_2}-x_{c'_2} \leq y_2 \\ \cdots\\ x_{c_m} - x_{c'_m}\leq y_m\end{cases}$$

的不等式组，求任意一组满足这个不等式组的解。

## 输入格式

第一行为两个正整数 $n,m$，代表未知数的数量和不等式的数量。

接下来 $m$ 行，每行包含三个整数 $c,c',y$，代表一个不等式 $x_c-x_{c'}\leq y$。

## 输出格式

一行，$n$ 个数，表示 $x_1 , x_2 \cdots x_n$ 的一组可行解，如果有多组解，请输出任意一组，无解请输出 `NO`。

## 输入输出样例 #1

### 输入 #1

```
3 3
1 2 3
2 3 -2
1 3 1
```

### 输出 #1

```
5 3 5
```

## 说明/提示

**样例解释**

$\begin{cases}x_1-x_2\leq 3 \\ x_2 - x_3 \leq -2 \\ x_1 - x_3 \leq 1 \end{cases}$

一种可行的方法是 $x_1 = 5, x_2 = 3, x_3 = 5$。

$\begin{cases}5-3  = 2\leq 3 \\ 3 - 5 = -2 \leq -2 \\ 5 - 5  = 0\leq 1 \end{cases}$

**数据范围**

对于 $100\%$ 的数据，$1\leq n,m \leq 5\times 10^3$，$-10^4\leq y\leq 10^4$，$1\leq c,c'\leq n$，$c \neq c'$。

**评分策略**

你的答案符合该不等式组即可得分，请确保你的答案中的数据在 `int` 范围内。

如果并没有答案，而你的程序给出了答案，SPJ 会给出 `There is no answer, but you gave it`，结果为 WA；    
如果并没有答案，而你的程序输出了 `NO`，SPJ 会给出 `No answer`，结果为 AC；       
如果存在答案，而你的答案错误，SPJ 会给出 `Wrong answer`，结果为 WA；    
如果存在答案，且你的答案正确，SPJ 会给出 `The answer is correct`，结果为 AC。




***

没关系！这题是典型的 **差分约束系统**（Difference Constraints System）问题，用 **SPFA** 或 **Bellman-Ford** 可以很好地求解。我们先一步一步解释，然后再给你完整代码。

---

## ✅ 差分约束系统简介

你给的约束都是这种形式：

```
x_c - x_c' ≤ y
```

这其实可以看成一个**图上的边权限制**，把它变形成：

```
x_c ≤ x_c' + y
```

也就是说，从 `x_c'` 到 `x_c` 有一条权值为 `y` 的边，表示：

> x\_c 的最小值不能超过 x\_c' + y。

所以我们可以把这个系统建成一张**有向图**，然后求解这些最短路径即可。

---

## ✅ 题目本质

* 每个变量 `x_i` 看作一个图中的点
* 每个约束 `x_c - x_c' ≤ y`，在图中添加一条从 `c' → c` 的边，权值为 `y`
* 然后我们构造一个**超级源点 0**，向所有点 `1~n` 连一条边权为 0 的边，这样能让所有点都“被访问到”，即支持**不连通图**

然后跑一遍 SPFA，得出的 `dis[i]` 就是每个 `x_i` 的一个可行值。

---

## ✅ 完整思路

1. 把每个不等式 `x_c - x_c' ≤ y` 转换为：从 `c' → c` 连一条权重为 `y` 的有向边
2. 添加超级源点 0，向所有点 `1~n` 连一条权重为 0 的边
3. 使用 **SPFA（Shortest Path Faster Algorithm）** 求解
4. 如果发现负环，就输出 `NO`
5. 否则输出从源点到每个点的最短路作为一个合法解

---

## ✅ 代码实现（AC 版）

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int N = 5005;
const int INF = 1e9;

int n, m;
vector<pair<int, int>> graph[N];
int dis[N], cnt[N];
bool inQueue[N];

bool spfa(int s) {
    memset(dis, 0x3f, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));
    memset(inQueue, false, sizeof(inQueue));

    dis[s] = 0;
    queue<int> q;
    q.push(s);
    inQueue[s] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        inQueue[u] = false;

        for (auto [v, w] : graph[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] > n) return false; // 有负环
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
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int c, c_, y;
        cin >> c >> c_ >> y;
        graph[c_].push_back({c, y});  // x_c - x_c' <= y 转为 c' → c
    }

    // 添加超级源点 0，向所有点连权重为 0 的边
    for (int i = 1; i <= n; i++) {
        graph[0].push_back({i, 0});
    }

    if (!spfa(0)) {
        cout << "NO" << endl;
    } else {
        for (int i = 1; i <= n; i++) {
            cout << dis[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
```

---

## 🔍 样例输入解释

输入：

```
3 3
1 2 3
2 3 -2
1 3 1
```

转换为图边：

```
2 → 1，权值 3
3 → 2，权值 -2
3 → 1，权值 1
```

加上源点：

```
0 → 1, 0
0 → 2, 0
0 → 3, 0
```

SPFA 最短路能得出一个合法解，如 `x_1 = 5, x_2 = 3, x_3 = 5`

---

要我给你画图解释一下这些约束是怎么变成图的吗？
