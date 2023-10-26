#include<stdio.h>
#define mod 1000000007
typedef long long ll;

ll mod_pow(ll x,ll n)
{
    ll res = 1;
    while(n > 0)
    {
        if(n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main()
{
    ll n, ans;
    scanf("%lld", &n);
    n++;
    ans = (mod_pow(3, n) - 1) * 500000004 % mod; 
    printf("%lld", ans);
    return 0;
}