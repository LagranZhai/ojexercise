#include <cstdio>

//并查集模板（仅路径压缩，无按秩合并）
//https://www.luogu.com.cn/problem/P1551

namespace uf {
    int fa[5001];
    inline void init(int n) { for (int i = 1; i <= n; ++i) fa[i] = i; }
    inline int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }
    inline void merge(int x, int y) { fa[find(x)] = find(y); }
}

int main() {
    int n, m, p; scanf("%d%d%d", &n, &m, &p);
    uf::init(n);
    for (int i = 0; i < m; ++i) {
        int x, y; scanf("%d%d", &x, &y); uf::merge(x, y);
    }
    for (int i = 0; i < p; ++i) {
        int x, y; scanf("%d%d", &x, &y); puts(uf::find(x) == uf::find(y) ? "Yes" : "No");
    }
    return 0;
}
