#include <stdio.h>
#define MAX 100001
#define ll long long

ll ans[MAX << 2], tag[MAX << 2], n, m, a[MAX];

void debug()
{
    printf("ans: ");
    for (int i = 1; i <= 30; i ++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
    printf("tag: ");
    for (int i = 1; i <= 30; i ++) {
        printf("%lld ", tag[i]);
    }
    printf("\n");
}

static inline ll t_l (ll p) { return p << 1; }
static inline ll t_r (ll p) { return (p << 1) + 1; }

static inline void push_up (ll p) {
    ans[p] = ans[t_l(p)] + ans[t_r(p)];
}

static inline void f (ll p, ll l, ll r) {
    tag[p] = tag[p] ^ 1;
    ans[p] = r - l + 1 - ans[p];
    // printf("ans[%lld] <- %lld\n", p, ans[p]);
    // debug();
}

void push_down (ll p, ll l, ll r) {
    if (tag[p]) {
        tag[p] = 0;
        ll mid = (l + r) >> 1;
        f(t_l(p), l, mid);
        f(t_r(p), mid + 1, r);
    }
}

void update (ll c_l, ll c_r, ll p, ll l, ll r) {
    if (c_l <= l && r <= c_r) {
        f(p, l, r);
        return;
    }
    push_down(p, l, r);
    ll mid = (l + r) >> 1;
    if (c_l <= mid) update(c_l, c_r, t_l(p), l, mid);
    if (mid + 1 <= c_r) update(c_l, c_r, t_r(p), mid + 1, r);
    push_up(p);
        // debug();
}

ll query(ll q_l, ll q_r, ll p, ll l, ll r) {
    if (q_l <= l && r <= q_r) return ans[p];
    push_down(p, l , r);
    ll mid = (l + r) >> 1;
    ll ret = 0;
    if (q_l <= mid) ret += query(q_l, q_r, t_l(p), l, mid);
    if (mid + 1 <= q_r) ret += query(q_l, q_r, t_r(p), mid + 1, r);
    return ret;
}



int main() {
    scanf("%lld%lld", &n, &m);
    ll s = 1;
    while (s < n) s <<= 1;
    int i;
    for (i = 0; i < m; i ++) {
        ll c, a, b;
        scanf("%lld%lld%lld", &c, &a, &b);
        if (c == 0) {
            update(a, b, 1, 1, s);
        } else {
            printf("%lld\n", query(a, b, 1, 1, s));
        }
    }
    return 0;
}