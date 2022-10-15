#include <list>
#include <cstdio>

//https://www.luogu.com.cn/problem/P3371

constexpr int MAXN = int(1e4+1), MAXM = int(5e5+1);
int head[MAXN], to[MAXM], next[MAXM], weight[MAXM], eid;
inline void addedge(int u, int v, int w) { to[++eid] = v; weight[eid] = w; next[eid] = head[u]; head[u] = eid; }

int dis[MAXN];
bool isinq[MAXN];

void spfa(int n, int s) {
    for (int i = 1; i <= n; ++i)
        dis[i] = 2147483647;
    dis[s] = 0;

    std::list<int> q;
    q.push_back(s);
    isinq[s] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        isinq[u] = false;
        for (int ed = head[u]; ed; ed = next[ed]) {
            int v = to[ed];
            //一定要松弛
            if (0LL + dis[u] + weight[ed] < dis[v]) {
                dis[v] = dis[u] + weight[ed];
                //不一定入队
                if (!isinq[v])
                    q.push_back(v), isinq[v] = true;
            }
        }
    }
}

int main() {
    int n, m, s; scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i < m; ++i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
    }

    spfa(n, s);

    for (int i = 1; i <= n; ++i)
        printf("%d ", dis[i]);
    return 0;
}
