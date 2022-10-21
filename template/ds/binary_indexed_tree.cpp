#include <cstdio>

//树状数组模板
//https://www.luogu.com.cn/problem/P3374

constexpr inline int lowbit(int x) { return x & (-x); }

int n, tree[500001];

inline void update(int i, int diff) {
    for (; i <= n; i += lowbit(i))
        tree[i] += diff;
}

inline int getsum(int i) {
    int ans = 0;
    for (; i; i -= lowbit(i))
        ans += tree[i];
    return ans;
}

int main() {
    int q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        int elem; scanf("%d", &elem); update(i, elem);
    }
    while (q--) {
        int op, x, y; scanf("%d%d%d", &op, &x, &y);
        if (op == 1) update(x, y);
        else printf("%d\n", getsum(y) - getsum(x-1));
    }
    return 0;
}
