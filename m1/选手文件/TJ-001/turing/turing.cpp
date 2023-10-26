#include <iostream>
using namespace std;
#define int long long
const int MOD = 998244353;
int n, x, y, a, b, c, d, e, f;
signed main() {
    freopen("turing.in", "r", stdin);
    freopen("turing.out", "r", stdout);
    cin >> n >> x >> y >> a >> b >> c >> d >> e >> f;
    if (b == d) cout << 1 << endl << a << ' ' << e << ' ' << c % MOD * f % MOD << endl;
    else cout << 0 << endl;
    return 0;
}