#include <cstdio>
#include <cstring>
#include <algorithm>

//多重背包模板，使用二进制优化
//https://www.luogu.com.cn/problem/P1776

constexpr int MAXN = 40001;

int maxweight, dp[MAXN];

inline void _01pack_update(int oneweight, int onevalue) {
    for (int w = maxweight; w >= oneweight; --w)
        dp[w] = std::max(dp[w], dp[w - oneweight] + onevalue);
}

int main() {
    int n; scanf("%d%d", &n, &maxweight);
    for (int i = 0; i < n; ++i) {
        int weight, value, cnt; scanf("%d%d%d", &value, &weight, &cnt);
        for (int factor = 1; cnt - factor >= 0; cnt -= factor, factor <<= 1)
            _01pack_update(weight * factor, value * factor);
        _01pack_update(weight * cnt, value * cnt);
    }
    printf("%d", dp[maxweight]);
    return 0;
}
