#include <cstdio>
#include <algorithm>

//完全背包模板
//https://www.luogu.com.cn/problem/P1616

long long dp[int(1e7+1)];

int main() {
    int t, m; scanf("%d%d", &t, &m);
    for (int i = 0; i < m; ++i) {
        int t0, m0; scanf("%d%d", &t0, &m0);
        for (int timecost = t0; timecost <= t; ++timecost)
            dp[timecost] = std::max(dp[timecost], dp[timecost - t0] + m0);
    }
    printf("%lld", dp[t]);
    return 0;
}
