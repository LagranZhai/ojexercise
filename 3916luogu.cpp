#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxn = 10e5 + 5;

struct Edge{
   int to,next;
}e[maxn];

int dfn[maxn],low[maxn],Time;
int s[maxn],top,vis[maxn];
int f[maxn],n,m;
int cnt,belong[maxn],MAX[maxn];
int k,x[maxn],y[maxn],head[maxn];

void add(int u,int v)
{
   e[++k].to = v;
   e[k].next = head[u];
   head[u] = k;
}

void tarjan(int x)  				 //求有向图强联通分量的tarjan，在这里不过多叙述，想学习的可以点链接去博客qwq 
{
   vis[x] = 1;
   s[++top] = x;
   dfn[x] = low[x] = ++Time;
   for(int i = head[x];i;i=e[i].next)
   {
       int to = e[i].to;
       if(!dfn[to])
       {
           tarjan(to);
           low[x] = min(low[x],low[to]);
       }
       else if(vis[to])
           low[x] = min(low[x],dfn[to]);
   }
   if(dfn[x] == low[x])			//如果x及其子树能够构成一个强联通分量 
   {
       ++cnt;
       int j;
       while(j=s[top])   			//将其子树中的点都加入此分量中,并将此分量中的最大值保存在MAX数组中 
       {
           vis[j] = 0;
           belong[j] = cnt;
           MAX[cnt] = max(MAX[cnt],j);
           top--;
           if(j==x) break;
       }
   }
}

void dfs(int x)    					//记忆化搜索 
{
   if(f[x]) return;
   f[x] = MAX[x];					//当前强联通分量中的最大值 
   for(int i=head[x];i;i=e[i].next)
   {
       int to = e[i].to;
       if(!f[to]) dfs(to);
       f[x] = max(f[x],f[to]);		// 子树中的最大值 
   }
}

int main()
{
   //freopen("data.in","r",stdin);
   //freopen("jkb.out","w",stdout);
   scanf("%d%d",&n,&m);
   for(int i=1;i<=m;i++)
   {
       scanf("%d%d",&x[i],&y[i]);			//保存边信息 
       add(x[i],y[i]);
   }
   for(int i=1;i<=n;i++)					//求出强联通分量 
       if(!dfn[i])
           tarjan(i);
   memset(e,0,sizeof(e));					//清空原图 
   memset(head,0,sizeof(head));	
   k = 0;
   for(int i=1;i<=m;i++)					//建立新图 
       if(belong[x[i]]!=belong[y[i]])
           add(belong[x[i]],belong[y[i]]);
   for(int i=1;i<=cnt;i++)
       if(!f[i]) dfs(i);
   for(int i=1;i<=n;i++)					//输出答案 
       printf("%d ",f[belong[i]]);
   return 0;
}
