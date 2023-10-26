#include <fstream>
#include <iostream>
#include <algorithm>
using std::cin; using std::cout; using std::endl; using std::cerr;
constexpr int MOD = int(1e9+7);
#define FILE_IN 1
#define FILE_OUT 1
constexpr int pow3(int x) {
    if (x == 0) return 1;
    int temp = pow3(x / 2);
    return 1LL * temp * temp * (x % 2 ? 3 : 1) % MOD;
}

int main() {
#if FILE_IN
#define cin ifs
    std::ifstream ifs("magic.in");
#endif // FILE_IN
#if FILE_OUT
#define cout ofs
    std::ofstream ofs("magic.out");
#endif // FILE_OUT
    //x  = 3^0 + 3^1 + 3^2 + ... + 3^n
    //3x =       3^1 + 3^2 + ... + 3^n + 3^(n+1)
    //2x = 3^(n+1)-1
    //x  = (3^(n+1)-1)/2
    int n; cin >> n;
    cout << 1LL * (pow3(n + 1) - 1) * int(5e8+4) % MOD << endl;
    return 0;
}
