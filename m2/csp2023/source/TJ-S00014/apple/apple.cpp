#include<bits/stdc++.h>
using namespace std;

stack <int>s;

const int N=50010;
int dis[N],head[N],n,k;

struct node{
	int to,next;
}e[N];

void add(int x,int y)
{
	cnt++;
	e[cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}

void dfs(int x)
{
	memset(dis,0x3f,sizeof(dis));
	dis[x]=0;
	
	
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		
	}
}
