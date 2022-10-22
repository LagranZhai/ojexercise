#include <cstdio>
#include <algorithm>

//01 背包模板
//https://www.luogu.com.cn/problem/P1048

int dp[1001];

int main() {
    int t, m; scanf("%d%d", &t, &m);
    for (int i = 0; i < m; ++i) {
        int t0, m0; scanf("%d%d", &t0, &m0);
        for (int timecost = t; timecost >= t0; --timecost)
            dp[timecost] = std::max(dp[timecost], dp[timecost - t0] + m0);
    }
    printf("%d", dp[t]);
    return 0;
}
