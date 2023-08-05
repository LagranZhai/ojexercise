#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <set>

//https://www.luogu.com.cn/problem/P3371
//https://www.luogu.com.cn/problem/P4779

//Dijkstra 单源最短路径

constexpr int MAXN = int(1e5+1), MAXM = int(2e5+1);

int head[MAXN], next[MAXM], to[MAXM], weight[MAXM], eid;
inline void addedge(int u, int v, int w) { to[++eid] = v; weight[eid] = w; next[eid] = head[u]; head[u] = eid; }

int dis[MAXN];
bool vis[MAXN];

using Node=std::pair<int,int >;
//struct Node { int curdis, id; };
//inline bool operator<(const Node& a, const Node& b) { return a.curdis > b.curdis; }


void dijkstra_search(int u) {
    std::memset(dis, 0x3f, sizeof(dis));
    dis[u] = 0;
    std::set<Node> q;
    q.insert(std::make_pair( 0, u ));
    while (!q.empty()) {
        Node top = *q.begin(); 
        q.erase(q.begin());
        if (!vis[top.second]) {
            vis[top.second] = true;
            for (int ed = head[top.second]; ed; ed = next[ed]) {
                if (!vis[to[ed]]) {
                    q.erase(std::make_pair(dis[to[ed]],to[ed]));
                    dis[to[ed]] = std::min(dis[to[ed]], dis[top.second] + weight[ed]);
                    q.insert(std::make_pair( dis[to[ed]], to[ed] ));
                }
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
    dijkstra_search(s);
    for (int i = 1; i <= n; ++i)
        printf("%d ", dis[i]);
    return 0;
}
