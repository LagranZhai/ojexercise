#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 500000 + 10

int t,n;
vector<int> a[N], b[N];
int cnt=1, num2[N], out[N];
int mk[N], d[2 * N];
int res[N];
int ww=0;
void DFS2(int u, int prev)
	{
		num2[u]=cnt++;
		for (int i=0; i < b[u].size(); i++)
			{
                int v = b[u][i];
			    if (v == prev) continue;
				if (num2[v] == 0)
					DFS2(v, u);
			}
        out[u]=cnt++;
	}
void update(int x, int val)
{
        while (x <= 2 * n)
            d[x]+=val, x+=x & (-x);
}
int get(int x)
{
        int rs=0;
        while (x > 0)
            rs+=d[x], x-=x & (-x);
        return rs;
}
void DFS1(int u, int prev)
    {
        res[u]=get(num2[u]);
        update(num2[u],1);
        update(out[u],-1);

        for (int i=0; i < a[u].size(); i++)
            {
                int v=a[u][i];
                if (v == prev) continue;
                DFS1(v, u);
            }
        update(num2[u],-1);
        update(out[u],1);
    }
int main()
{
	freopen("climb.in","r",stdin);
	freopen("climb.out","w",stdout);
	scanf("%d", &n);
	for (int i=1; i <= n; i++)
	{
		a[i].clear();
		b[i].clear();
		num2[i]=out[i] =d[i] =res[i]=0;
		cnt = 1;
	}
	for (int i=1; i < n; i++)
	{
		int u,v;
		scanf("%d%d", &u, &v);
		a[u].push_back(v);
		a[v].push_back(u);
	}
	for (int i=1; i < n; i++)
	{
		int u,v;
		scanf("%d%d", &u, &v);
		b[u].push_back(v);
		b[v].push_back(u);
	}
	DFS2(1, 0);
	DFS1(1, 0);
	long long ans = 0;
	for (int i=1; i <= n; i++) {
		ans += res[i];
	}
	printf("%lld\n", ans);
	return 0;
}