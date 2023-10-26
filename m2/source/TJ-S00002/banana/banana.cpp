#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;
#define endl '\n'
const int N = 1055, M = 20055, MOD = 1e9 + 7;
int T, n, m, a[N], b[M], dp[2][M], cnt;
map<int, int> mp;
void func(int x) {
	b[++cnt] = x;
	mp[x] = cnt;
}
signed main() {
	freopen("banana.in", "r", stdin);
	freopen("banana.out", "w", stdout);
	cin.tie(0), ios_base::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cnt = 0;
		mp.clear();
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		cin >> n >> m;
		for (int i = 1; i * i <= m; i++) {
			if (m == i * i) func(i);
			else if (m % i == 0) func(i), func(m / i);
		}
		for (int i = 1; i <= n; i++) cin >> a[i];
		bool f = false;
		memset(dp, 0, sizeof(dp));
		dp[!f][1] = 1;
		for (int i = 1; i <= n; i++, f ^= 1) {
			for (int j = 1; j <= cnt; j++) 
				dp[f][j] = dp[!f][j];
			if (!a[i]) continue;
			if (m % a[i] == 0) {
				for (int j = 1; j <= cnt; j++) {
					if (b[j] % a[i] == 0) 
						(dp[f][j] += dp[!f][mp[b[j] / a[i]]]) %= MOD;
				}
			}
		}
		if (m == 1) cout << dp[!f][1] << endl;
		else cout << dp[!f][2] << endl;
	}
	return 0;
}
