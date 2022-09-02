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

void tarjan(int x)  				 //������ͼǿ��ͨ������tarjan�������ﲻ������������ѧϰ�Ŀ��Ե�����ȥ����qwq 
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
   if(dfn[x] == low[x])			//���x���������ܹ�����һ��ǿ��ͨ���� 
   {
       ++cnt;
       int j;
       while(j=s[top])   			//���������еĵ㶼����˷�����,�����˷����е����ֵ������MAX������ 
       {
           vis[j] = 0;
           belong[j] = cnt;
           MAX[cnt] = max(MAX[cnt],j);
           top--;
           if(j==x) break;
       }
   }
}

void dfs(int x)    					//���仯���� 
{
   if(f[x]) return;
   f[x] = MAX[x];					//��ǰǿ��ͨ�����е����ֵ 
   for(int i=head[x];i;i=e[i].next)
   {
       int to = e[i].to;
       if(!f[to]) dfs(to);
       f[x] = max(f[x],f[to]);		// �����е����ֵ 
   }
}

int main()
{
   //freopen("data.in","r",stdin);
   //freopen("jkb.out","w",stdout);
   scanf("%d%d",&n,&m);
   for(int i=1;i<=m;i++)
   {
       scanf("%d%d",&x[i],&y[i]);			//�������Ϣ 
       add(x[i],y[i]);
   }
   for(int i=1;i<=n;i++)					//���ǿ��ͨ���� 
       if(!dfn[i])
           tarjan(i);
   memset(e,0,sizeof(e));					//���ԭͼ 
   memset(head,0,sizeof(head));	
   k = 0;
   for(int i=1;i<=m;i++)					//������ͼ 
       if(belong[x[i]]!=belong[y[i]])
           add(belong[x[i]],belong[y[i]]);
   for(int i=1;i<=cnt;i++)
       if(!f[i]) dfs(i);
   for(int i=1;i<=n;i++)					//����� 
       printf("%d ",f[belong[i]]);
   return 0;
}
