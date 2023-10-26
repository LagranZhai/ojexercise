#include <iostream>
using std::cin; using std::cout; using std::endl;
constexpr int MOD = 998442353;
int main() {
    freopen("turing.in", "r", stdin);
    freopen("turing.out", "w", stdout);
    int n, r1, c1, x1, r2, c2, x2, useless;
    cin >> n >> useless >> useless;
    cin >> r1 >> c1 >> x1;
    cin >> r2 >> c2 >> x2;
    if (c1 == r2)
        cout << "1\n" << r1 << " " << c2 << " " << 1LL * x1 * x2 % MOD << endl;
    else
        cout << "0" << endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}