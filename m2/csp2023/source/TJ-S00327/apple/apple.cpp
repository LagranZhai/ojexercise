#include<bits/stdc++.h>
using namespace std;
#define N 50004
struct edge{
	int to,nex;
}e[N<<1];
int head[N],fa[N],maxx,pos;
bool vis[N];
void dfs(int p,int dep)
{
	if (dep>maxx || (dep==maxx&&p<pos))maxx=dep,pos=p;
	for(int i=head[p];i;i=e[i].nex)
	{
		int v=e[i].to;
		if(v==fa[p])continue;
		fa[v]=p;
		dfs(v,dep+(vis[v]?0:1));
	}
}
signed main()
{
	freopen("apple.in","r",stdin);
	freopen("apple.out","w",stdout);
	ios::sync_with_stdio(0);
	int n,k;
	cin>>n>>k;cout<<k<<'\n';k++;
	for(int i=2,fa;i<=n;i++)
	{
		cin>>fa;fa++;
		e[((i-1)<<1)-1].to=fa,e[((i-1)<<1)-1].nex=head[i],head[i]=((i-1)<<1)-1;
		e[(i-1)<<1].to=i,e[(i-1)<<1].nex=head[fa],head[fa]=(i-1)<<1;
	}
	vis[k]=1;
	while(1)
	{
		maxx=0;fa[k]=0;
		dfs(k,0);
		if(maxx==0)return 0;
		cout<<pos-1<<'\n';
		int tmp=pos;
		while(tmp!=k)
			vis[tmp]=1,tmp=fa[tmp];
		k=pos;
	}
}
