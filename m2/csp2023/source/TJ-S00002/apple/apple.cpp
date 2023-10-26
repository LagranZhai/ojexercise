#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
using namespace std;
#define int long long
#define endl '\n'
const int N = 5e4 + 55;
vector<int> g[N];
int n, m, a[N], dep[N], fa[N];
bool b[N];
struct node {
	int i, x;
	bool operator <(const node a) const {
		if (x == a.x) return i < a.i;
		return x > a.x;
	}
};
set<node> s;
void dfs(int x, int f, int de, int t) {
	if (g[x].size() == 1 && x != m) 
		s.insert({x, de}); 
	a[x] = t, fa[x] = f, dep[x] = de;
	for (int i = 0; i < g[x].size(); i++) {
		int u = g[x][i];
		if (u == f) continue;
		if (x == m) t = u;
		dfs(u, x, de + 1, t);
	}
}
void dfs2(int x, int f, int de, int t) {
	if (g[x].size() == 1 && dep[x]) {
		s.erase({x, dep[x]});
		dep[x] = de;
		a[x] = t;
		s.insert({x, dep[x]});
	}
	if (b[x]) t = x;
	for (int i = 0; i < g[x].size(); i++) {
		int u = g[x][i];
		if (u == f) continue;
		dfs2(u, x, de + 1, t);
	}
}
signed main() {
	freopen("apple.in", "r", stdin);
	freopen("apple.out", "w", stdout);
	cin.tie(0), ios_base::sync_with_stdio(false);
	cin >> n >> m;
	m++;
	for (int i = 2, x; i <= n; i++) {
		cin >> x, g[i].push_back(x + 1), g[x + 1].push_back(i);
	}
	dfs(m, m, 0, 0);
	cout << m - 1 << endl;
	while (!s.empty()) {
		int x = s.begin() -> i;
		s.erase(s.begin());
		dep[x] = 0;
		for (int j = x; j != fa[a[x]]; j = fa[j]) 
			b[x] = true;
		dfs2(a[x], fa[a[x]], 0, a[x]);
		for (int j = x; j != fa[a[x]]; j = fa[j]) 
			b[x] = false;
		cout << x - 1 << endl;
	}
	return 0;
}
