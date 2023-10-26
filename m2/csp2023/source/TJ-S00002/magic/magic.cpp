#include <iostream>
#include <cstdio>
using namespace std;
#define int long long
#define endl '\n'
const int MOD = 1e9 + 7, K = 5e8 + 4;
int n;
int pow_mod(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) (res *= a) %= MOD;
		(a *= a) %= MOD, b >>= 1;
	}
	return res;
}
signed main() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	cin.tie(0), ios_base::sync_with_stdio(false);
	cin >> n;
	cout << (((pow_mod(3, n + 1) - 1) % MOD + MOD) % MOD) * K % MOD << endl;
	return 0;
}
