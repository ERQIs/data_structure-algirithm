#include <stdio.h>
#define MAX 100001
#define ll long long

ll ans[MAX << 2], tag[MAX << 2], n, m, a[MAX];

static inline ll t_left (ll x) { return x << 1; }
static inline ll t_right (ll x) { return (x << 1) + 1; }

static inline void push_up(ll p) {
    ans[p] = ans[t_left(p)] + ans[t_right(p)]; 
}

void build(ll p, ll left, ll right) {
    tag[p] = 0;
    if (left == right) {
        ans[p] = a[left];
        return;
    }
    ll mid = left + ((right - left) >> 1);
    build(t_left(p), left, mid);
    build(t_right(p), mid + 1, right);
    push_up(p);
}

static inline void f (ll p, ll left, ll right, ll k) {
    tag[p] = tag[p] + k;
    ans[p] = ans[p] + (right - left + 1) * k;
}

void push_down(ll p, ll left, ll right) {
    ll mid = left + ((right - left) >> 1);
    f(t_left(p), left, mid, tag[p]);
    f(t_right(p), mid + 1, right, tag[p]);
    tag[p] = 0;
}

void update(ll change_l, ll change_r,ll p, ll left, ll right, ll k) {
    if (change_l <= left && right <= change_r) {
        f(p, left, right, k);
        return;
    }
    push_down(p, left, right);
    ll mid = left + ((right - left) >> 1);
    if (change_l <= mid) update(change_l, change_r, t_left(p), left, mid, k);
    if (change_r >= mid + 1) update(change_l, change_r, t_right(p), mid + 1, right, k);
    push_up(p);
}

ll query (ll q_l, ll q_r, ll left, ll right, ll p) {
    ll res = 0;
    if (q_l <= left && right <= q_r) {
        return ans[p];
    }
    ll mid = left + ((right - left) >> 1);
    push_down(p, left, right);
    if (q_l <= mid) res += query(q_l, q_r, left, mid, t_left(p));
    if (q_r >= mid + 1) res += query(q_l, q_r, mid + 1, right, t_right(p));
    return res;
}

void scan() {
    int i;
    scanf("%lld%lld", &n, &m);
    for (i = 1; i <= n; i ++) {
        scanf("%lld", &a[i]);
    }
}

int main()
{
    scan();
    build(1, 1, n);
    int c, i;
    ll x, y, k;
    for (i = 0; i < m; i ++) {
        scanf("%d", &c);
        if (c == 1) {
            scanf("%lld%lld%lld", &x, &y, &k);
            update(x, y, 1, 1, n, k);
        } else {
            scanf("%lld%lld", &x, &y);
            printf("%lld\n", query(x, y, 1, n, 1));
        }
    }
    return 0;
}