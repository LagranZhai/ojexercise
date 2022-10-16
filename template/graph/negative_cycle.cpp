#include <list>
#include <cstdio>
#include <cstring>

//https://www.luogu.com.cn/problem/P3385

//判断图中有没有负环

constexpr int MAXN = int(2e3+1), MAXM = int(6e3+1);
int head[MAXN], to[MAXM], next[MAXM], weight[MAXM], eid;
inline void addedge(int u, int v, int w) { to[++eid] = v; weight[eid] = w; next[eid] = head[u]; head[u] = eid; }

int dis[MAXN];
int cnt[MAXN];
bool isinq[MAXN];

bool spfa(int n, int s) {
    for (int i = 1; i <= n; ++i)
        dis[i] = 0x3f3f3f3f;
    dis[s] = 0;
    std::memset(cnt, 0, sizeof(cnt));
    std::memset(isinq, 0, sizeof(isinq));

    std::list<int> q;
    q.push_back(s);
    isinq[s] = true;
    cnt[s] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        isinq[u] = false;
        for (int ed = head[u]; ed; ed = next[ed]) {
            int v = to[ed];
            if (dis[u] + weight[ed] < dis[v]) {
                dis[v] = dis[u] + weight[ed];
                if (!isinq[v]) {
                    q.push_back(v), isinq[v] = true;
                    if (++cnt[v] >= n)
                        return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int n, m, t; scanf("%d", &t);
    while (t--) {
        std::memset(head, 0, sizeof(head));
        std::memset(to, 0, sizeof(to));
        std::memset(next, 0, sizeof(next));
        std::memset(weight, 0, sizeof(weight));
        eid = 0;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            if (w >= 0) addedge(v, u, w);
        }

        puts(spfa(n, 1) ? "YES" : "NO");
    }
    return 0;
}
