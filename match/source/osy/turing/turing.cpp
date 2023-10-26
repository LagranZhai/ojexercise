#include <iostream>

constexpr int MOD = 998442353;

int main() {
    using std::cin; using std::cout; using std::endl;

    int n, useless_variable; cin >> n >> useless_variable >> useless_variable;
    int r1, c1, x1, r2, c2, x2; cin >> r1 >> c1 >> x1 >> r2 >> c2 >> x2;
    if (c1 == r2) cout << r1 << " " << c2 << " " << (1LL * x1 * x2 % MOD) << endl;
    else cout << "0" << endl;
    
    return 0;
}