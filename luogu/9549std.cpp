#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#define int long long
using namespace std;
int n,m,k,g,a[110],b[110],c[110];
int d[110][110][110];
bool flag[110][110][110];
struct Edge{
    int v{0},nxt{0},p{0},q{0};
}edge[330];
int head[220],cnt{0};
void addedge(int u,int v,int p,int q){
    edge[++cnt].v=v;
    edge[cnt].p=p;
    edge[cnt].q=q;
    edge[cnt].nxt=head[u];
    head[u]=cnt;
}
// struct edge{int x,p,q;};
// vector<edge>v[110];
struct node{int x,lim,cnt,dis;};
bool operator<(const node &x,const node &y){
    return x.dis>y.dis;
}
priority_queue<node>qq;
void go(int x,int limx,int cntx,int y,int limy,int cnty,int w)
{
    if(d[x][limx][cntx]+w<d[y][limy][cnty])
    {
        d[y][limy][cnty]=d[x][limx][cntx]+w;
        qq.push({y,limy,cnty,d[y][limy][cnty]});
    }
}
void dij()
{
    qq.push({1,0,0,0});
    memset(d,999999,sizeof(d));
    d[1][0][0]=0;
    while(!qq.empty())
    {
        int x=qq.top().x,lim=qq.top().lim;
        int cnt=qq.top().cnt,dis=qq.top().dis;
        qq.pop();
        int t=a[x]+b[x]+c[x],now=dis%t;
        if(x==n)
        {
            cout<<dis<<endl;
            return ;
        }
        if(flag[x][lim][cnt])continue;
        flag[x][lim][cnt]=1;
        for(int e{head[x]};e;e=edge[e].nxt)
        {
            int p=edge[e].p,q=edge[e].q;
            if(now<a[x])//绿灯
            {
                //限速
                go(x,lim,cnt,edge[e].v,lim,cnt,q);
                //不限速
                if(lim<m-k)go(x,lim,cnt,edge[e].v,lim+1,cnt,p);
            }
            else if(now<a[x]+b[x])//黄灯
            {
                //不闯黄灯，限速
                go(x,lim,cnt,edge[e].v,lim,cnt,t-now+q);
                //不闯黄灯，不限速
                if(lim<m-k)go(x,lim,cnt,edge[e].v,lim+1,cnt,t-now+p);
                //闯黄灯，限速
                if(cnt<g)go(x,lim,cnt,edge[e].v,lim,cnt+1,q);
                //闯黄灯，不限速
                if(cnt<g&&lim<m-k)
                    go(x,lim,cnt,edge[e].v,lim+1,cnt+1,p);
            }
            else//红灯
            {
                //限速
                go(x,lim,cnt,edge[e].v,lim,cnt,t-now+q);
                //不限速
                if(lim<m-k)go(x,lim,cnt,edge[e].v,lim+1,cnt,t-now+p);
            }
        }
    }
}
signed main()
{
    int qsa;
    cin>>qsa;
    cerr<<"a";
    cin>>n>>m>>k>>g;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];
    for(int i=1;i<=m;i++)
    {
        int x,y,p,q;
        cin>>x>>y>>p>>q;
        // v[x].push_back({y,p,q});
        // v[y].push_back({x,p,q});
        addedge(x,y,p,q);
        addedge(y,x,p,q);
    }
    dij();
    return 0;
}

