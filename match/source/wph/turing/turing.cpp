#include <iostream>
using namespace std;
typedef long long LL;
const LL mod = 998442353;
int n, a, b, x, y, xx, yy;
LL z1, z2;
int main() {
	freopen("turing.in", "r", stdin);
	freopen("turing.out", "w", stdout);
	scanf("%d %d %d", &n, &a, &b);
	scanf("%d %d %lld", &x, &y, &z1);
	scanf("%d %d %lld", &xx, &yy, &z2);
	if (z1 == 0 || z2 == 0 || y != xx) {
		printf("0\n");
	} else {
		printf("1\n%d %d %d\n", x, yy, (z1 % mod) * (z2 % mod) % mod);
	}
	return 0;
}
