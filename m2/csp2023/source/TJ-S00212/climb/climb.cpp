#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>
#define FILE_IN 1
#define FILE_OUT 1
using std::cin; using std::cout; using std::endl; using std::cerr;
constexpr int MAXN = int(1e5+5), MAXM = MAXN * 2;
int head1[MAXN], next1[MAXM], to1[MAXM], eid1 = 1;
int head2[MAXN], next2[MAXM], to2[MAXM], eid2 = 1;
inline void addedge1(int u, int v) { to1[eid1] = v; next1[eid1] = head1[u]; head1[u] = eid1++; }
inline void addedge2(int u, int v) { to2[eid2] = v; next2[eid2] = head2[u]; head2[u] = eid2++; }
int father[MAXN], answer = 0;
std::set<std::pair<int, int>> record;
void dfs1(int u, int fa) {
    int child = 0; father[u] = fa;
    for (int ed = head1[u]; ed; ed = next1[ed])
        if (to1[ed] != fa)
            dfs1(to1[ed], u), ++child;
    if (child == 0)
        for (int origin = u; u; u = father[u])
            for (int v = origin; v != u; v = father[v])
                record.emplace(u, v);
}
void dfs2(int u, int fa) {
    int child = 0; father[u] = fa;
    for (int ed = head2[u]; ed; ed = next2[ed])
        if (to2[ed] != fa)
            dfs2(to2[ed], u), ++child;
    if (child == 0)
        for (int origin = u; u; u = father[u])
            for (int v = origin; v != u; v = father[v])
                if (record.count(std::make_pair(u, v)))
                    ++answer, record.erase(std::make_pair(u, v));
}


int main() {
#if FILE_IN
#define cin ifs
    std::ifstream ifs("climb.in");
#endif
#if FILE_OUT
#define cout ofs
    std::ofstream ofs("climb.out");
#endif
    int n; cin >> n;
    for (int i = 0, u, v; i < n-1; ++i)
        cin >> u >> v, addedge1(u, v), addedge1(v, u);
    cerr << "tree1 input OK.\n";
    for (int i = 0, u, v; i < n-1; ++i)
        cin >> u >> v, addedge2(u, v), addedge2(v, u);
    cerr << "tree2 input OK.\n";
    dfs1(1, 0);
    dfs2(1, 0);
    cout << answer << endl;
    return 0;
}

