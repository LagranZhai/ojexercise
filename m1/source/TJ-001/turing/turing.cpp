#include <iostream>
using namespace std;
#define int long long
const int MOD = 998244353;
int n, x, y, a, b, c, d, e, f;
signed main() {
    freopen("turing.in", "r", stdin);
    freopen("turing.out", "w", stdout);
    cin >> n >> x >> y >> a >> b >> c >> d >> e >> f;
    if (b == d) cout << 1 << "\n" << a << ' ' << e << ' ' << c % MOD * f % MOD << "\n";
    else cout << 0 << "\n";
    cout << flush;
    return 0;
}