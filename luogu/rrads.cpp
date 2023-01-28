#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 500010;

int n , m , t1 , w1 , ans , num , len , tou , wei , pos[N] , sum[N];
pair<int , int> a[N];

struct List
{
    int hou , qian , val;
}q[N] , h[N];

struct Modui
{
    int l , r , id;
    inline bool operator<(const Modui &tmp) const
    {
        return pos[l] == pos[tmp.l] ? r > tmp.r : pos[l] < pos[tmp.l];
    }
}que[N];

#define l(x) (x - 1) * len + 1
#define r(x) min(x * len , n)

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}

inline void del(int x)
{
    if(x != tou) ans -= abs(x - q[x].qian);
    if(x != wei) ans -= abs(x - q[x].hou);
    if(x != tou && x != wei) ans += abs(q[x].qian - q[x].hou);
    if(x == tou) tou = q[x].hou;
    if(x == wei) wei = q[x].qian;
    q[q[x].qian].hou = q[x].hou;
    q[q[x].hou].qian = q[x].qian;
}

inline void add(int x)
{
    q[q[x].qian].hou = x;
    q[q[x].hou].qian = x;
}

inline void cp(List *x , List *y)
{
    for(int i = 1;i <= n;i++)
        x[i] = y[i];
}

signed main()
{
    freopen("rrads.in","r",stdin);
    freopen("rrads.out","w",stdout);
    n = read() , m = read() , len = sqrt(n);
    for(int i = 1;i <= n;i++)
        a[i].first = read() , a[i].second = i;
    sort(a + 1 , a + n + 1) , tou = a[1].second , wei = a[n].second;
    for(int i = 1;i <= n;i++)
        q[a[i].second].qian = a[i - 1].second,
        q[a[i].second].hou = a[i + 1].second;
    for(int i = 1;i <= n;i++) 
        pos[i] = (i - 1) / len + 1;
    for(int i = 1;i <= n;i++)
        if(i != tou) ans += abs(i - q[i].qian);
    for(int i = 1;i <= m;i++)
        que[i].l = read() , que[i].r = read() , que[i].id = i;
    sort(que + 1 , que + m + 1);
    for(int j = 1 , k = 1 , l = 1 , r = n;j <= pos[n] && k <= m;j++)
    {
        if(pos[que[k].l] == j)
        {
            while(l < l(j)) del(l++); 
            cp(h , q) , num = ans;
            t1 = tou , w1 = wei;
            while(pos[que[k].l] == j)
            {
                while(r > que[k].r) del(r--);
                int su = ans , tt = tou , ww = wei;
                while(l < que[k].l) del(l++);
                sum[que[k].id] = ans;
                while(l > l(j)) add(--l);
                k++ , ans = su , tou = tt , wei = ww;
            }
            cp(q , h) , ans = num;
            tou = t1 , wei = w1 , r = n;
        }
    }
    for(int i = 1;i <= m;i++) printf("%lld\n" , sum[i]);
    return 0;
}