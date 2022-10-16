#include <cstdio>
#include <cstring>
#include <algorithm>

//https://www.luogu.com.cn/problem/P3366

//Kruskal 算法求最小生成树

constexpr int MAXN = 5001, MAXM = int(4e5);

struct Edge { int from, to, weight; } edges[MAXM];

bool ptvis[MAXN];

namespace uf {
    int fa[MAXN];
    inline void init(int n) { for (int i = 1; i <= n; ++i) fa[i] = i; }
    inline int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }
    inline void merge(int x, int y) { fa[find(x)] = find(y); }
}

int kruskal(int n, int m) {
    uf::init(n);
    std::sort(edges, edges + m, [](const Edge& ea, const Edge& eb){ return ea.weight < eb.weight; });
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        if (uf::find(edges[i].from) != uf::find(edges[i].to)) {
            uf::merge(edges[i].from, edges[i].to);
            ans += edges[i].weight;
        }
    }
    return ans;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
        scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].weight);
    uf::init(n);
    for (int i = 0; i < m; ++i)
        uf::merge(edges[i].from, edges[i].to);
    for (int i = 2; i <= n; ++i) {
        if (uf::find(i) != uf::find(1)) {
            puts("orz"); return 0;
        }
    }
    printf("%d", kruskal(n, m));
    return 0;
}
