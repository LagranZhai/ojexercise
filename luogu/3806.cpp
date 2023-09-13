#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using std::cin,std::cout,std::ios;
constexpr int const maxn=1e4,maxm=100,maxk=1e7;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
    // std::ifstream in("P3806_1.in");
    // // std::ofstream out("P3806.out");
struct Edge{
    int v=0,nxt=0,w=0;
}edg[maxn*3];
int head[maxn*2],cnt=0;
void addedge(int u,int v,int w){
    edg[++cnt].v=v;
    edg[cnt].w=w;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    return ;
}
int n,m;
int q[maxm*2];
int fa[maxn*2],siz[maxn*2],maxss[maxn*2];
int dis[maxn*2];
bool vis[maxn*2];
void dfs1(int x,int f){
    siz[x]=1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&vis[to]==0){
            dfs1(to,x);
            siz[x]+=siz[to];
        }
    }
}
int dfs2(int x,int f,int sum){
    maxss[x]=sum-siz[x];
    int minms=maxn*2;int minmsp=0;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&vis[to]==0){
            int p=dfs2(to,x,sum);
            maxss[x]=std::max(maxss[x],siz[to]);
            if(maxss[p]<minms){
                minms=maxss[p];
                minmsp=p;
            }
        }
    }
    if(maxss[x]<minms){
        minmsp=x;
    }
    return minmsp;
}
int gc(int x,int f){
    dfs1(x,f);
    return dfs2(x,f,siz[x]);
}
bool ans[maxm*2];
bool c[maxk+100];
std::vector<int > num;
void dfs3(int x,int f){
    for(int i{1};i<=m;i++){
        if(q[i]>=dis[x]&&c[q[i]-dis[x]]){
            ans[i]=1;
        }
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&vis[to]==0){
            dis[to]=dis[x]+edg[e].w;
            if(dis[to]<=maxk)dfs3(to,x);
        }
    }
}
void dfs4(int x,int f){
    c[dis[x]]=1;
    num.push_back(dis[x]);
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&vis[to]==0){
            if(dis[to]<=maxk)dfs4(to,x);
        }
    }
}

void calc(int x){
    // std::cerr<<x<<"\n";
    // std::fill(c,c+maxk,false);
    num.clear();
    dis[x]=0;
    c[0]=1;
    num.push_back(0);
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(vis[to]==0){
            dis[to]=edg[e].w;
            dfs3(to,x);
            // std::cerr<<to<<"\n";
            dfs4(to,x);
        }
    }
    for(int &a:num){
        c[a]=0;
    }
}
void solve(int x,int f){
    int ct{gc(x,f)};
    // std::cerr<<ct<<"\n";
    vis[ct]=1;
    calc(ct);
    for(int e{head[ct]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&vis[to]==0){
            solve(to,ct);
        }
    }
}
int main(){
    // ios::sync_with_stdio(false);
    cin>>n>>m;
    int u,v,w;
    for(int i{1};i<n;i++){
        // cin>>u>>v>>w;
        u=read();v=read();w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i{1};i<=m;i++){
        q[i]=read();
    }
    maxss[0]=n;
    solve(1,0);
    for(int i{1};i<=m;i++){
        if(ans[i])cout<<"AYE\n";
        else cout<<"NAY\n";
    }
    cout<<std::flush;
    return 0;  
}