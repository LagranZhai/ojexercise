#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using std::cin,std::cout,std::ios;
constexpr int const maxn=2e5,maxk=1e6;
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
int n,k;
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
    return (maxss[x]<minms?x:minmsp);
}
int gc(int x,int f){
    dfs1(x,f);
    return dfs2(x,f,siz[x]);
}
int ans=maxn*2;
int c[maxk+100];
std::vector<int > num;
void dfs3(int x,int f,int en){
    if(k>=dis[x]&&c[k-dis[x]]){
        ans=std::min(ans,c[k-dis[x]]+en-1);
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&vis[to]==0){
            dis[to]=dis[x]+edg[e].w;
            if(dis[to]<=maxk)dfs3(to,x,en+1);
        }
    }
}
void dfs4(int x,int f,int en){
    if(c[dis[x]]==0)c[dis[x]]=en+1;
    else c[dis[x]]=std::min(en+1,c[dis[x]]);
    num.push_back(dis[x]);
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&vis[to]==0){
            if(dis[to]<=maxk)dfs4(to,x,en+1);
        }
    }
}
void calc(int x){
    num.clear();
    dis[x]=0;
    c[0]=1;
    num.push_back(0);
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(vis[to]==0){
            dis[to]=edg[e].w;
            dfs3(to,x,1);
            // std::cerr<<to<<"\n";
            dfs4(to,x,1);
        }
    }
    for(int &a:num){
        c[a]=0;
    }
}
void solve(int x,int f){
    int ct{gc(x,f)};
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
    ios::sync_with_stdio(false);
    cin>>n>>k;
    int u,v,w;
    for(int i{1};i<n;i++){
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    maxss[0]=n;
    solve(1,0);
    cout<<(ans==maxn*2?-1:ans)<<std::endl;
    return 0;  
}