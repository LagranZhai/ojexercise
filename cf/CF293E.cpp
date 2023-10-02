#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using std::cin,std::cout,std::ios;
constexpr int const maxn=1e5,maxk=1e9;
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
int n,l,w;
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
long long ans=0;
int dep[maxn*2];
std::vector<int > c;
std::vector<int > num;
long long b[maxn+100];
inline int lowbit(int x){
    return x&(-x);
}
void update(int x,int w){
    // if(x==0)return ;
    while(x<=maxn){
        b[x]+=w;
        x+=lowbit(x);
    }
    return ;
}
long long query(int x){
    long long ans=0;
    if(x<=0)return 0;
    while(x){
        ans+=b[x];
        x-=lowbit(x);
    }
    return ans;
}
void dfs3(int x,int f){
    c.push_back(x);
    num.push_back(x);
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&vis[to]==0){
            dis[to]=dis[x]+edg[e].w;
            dep[to]=dep[x]+1;
            if(dep[to]<=l&&dis[to]<=w)dfs3(to,x);
        }
    }
}
std::vector<int > del;
long long calc1(std::vector<int > &c,bool flag){
    if(c.empty())return 0;
    long long res=0;
    std::sort(std::begin(c),std::end(c),[](const int a,const int b){return dis[a]<dis[b];});
    int e=c.size()-1;
    while(e>=0&&dis[c[e]]+dis[c[0]]>w)e--;
    for(int i{0};i<c.size();i++){
        int a{c[i]};
        if(flag){
            if(dep[i]<=l&&dis[i]<=w)res+=1;
        }
        update(dep[a],1);
        for(int j{i+1};j<c.size();j++){
            if(dis[c[j]]+dis[a]<=w){
                res+=query(l-dep[c[j]]);
            }
        }
        
        // int s=0;
        // while(e>i&&((i+1>=c.size())||(dis[c[e]]+dis[c[i+1]]>w))){
        //     s+=query(l-dep[c[e]]);
        //     e--;
        // }
        // res+=s*(i+1);
        // res+=query(r-dep[a])*dis[a]-query(l-dep[a]-1)*dis[a];
        // if(flag&&dep[a]>=l&&dep[a]<=r)res+=dis[a];
        
        del.push_back(dep[a]);
    }
    for(int &a:del){
        update(a,-1);
    }
    del.clear();
    return res;
}
void calc(int x){
    num.clear();
    // dis[x]=0;
    // c[0]+=1;
    // num.push_back(0);
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(vis[to]==0){
            dis[to]=edg[e].w;
            dep[to]=1;
            dfs3(to,x);
            ans-=calc1(c,0);
            // std::cerr<<to<<"\n";
            // dfs4(to,x);
            c.clear();
        }
    }
    ans+=calc1(num,1);
    // num.clear();
}
void solve(int x,int f){
    int ct{gc(x,f)};
    // cout<<ct<<"\n";
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
    cin>>n>>l>>w;
{
    int l,w;
    for(int i{1};i<n;i++){
        cin>>l>>w;
        addedge(i+1,l,w);
        addedge(l,i+1,w);
    }
}
    maxss[0]=n;
    solve(1,0);
    cout<<ans<<std::endl;
    return 0;  
}