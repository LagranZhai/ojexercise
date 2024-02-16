//PUVA1205
#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
using std::cerr;
#define int long long
constexpr int maxn=1e5;
int a[maxn];
struct Edge{
    int v,nxt;
}edg[maxn*2];
int head[maxn],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int n,r;
int fa[maxn];
void dfs(int x,int f){
    fa[x]=f;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x);
        }
    }
}

struct pii{
    int first,second;
    int x;
};
auto cmp=[](const pii A,const pii B){
    if(A.second*B.first==B.second*A.first){
        return A.x<B.x;
    }
    else return A.second*B.first<B.second*A.first;};
std::set<pii,decltype(cmp)> s(cmp);
namespace dsu{
    int fa[maxn];
    std::set<pii,decltype(cmp)>::iterator val[maxn];
    int getf(int x){
        return (fa[x]==x)?x:fa[x]=getf(fa[x]);
    }
    void merge(int x,int y){
        int fx{getf(x)},fy(getf(y));
        if(fx!=fy){
            fa[fx]=fy;
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>r;
    for(int i{1};i<=n;i++){
        cin>>a[i];
        dsu::fa[i]=i;
        auto res=s.insert({a[i],1,i});
        dsu::val[i]=res.first;
        // cerr<<res.second<<"\n";
    }
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(r,0);
    int ans{0};
    while(s.size()>1){
        pii cur{*s.begin()};
        if(cur.x==r){
            auto t{s.begin()};
            cur=*(++t);
        }
        s.erase(cur);
        int fn{dsu::getf(fa[cur.x])};
        pii f{*dsu::val[fn]};
        s.erase(dsu::val[fn]);
        dsu::merge(cur.x,fn);
        ans+=cur.first*f.second;
        dsu::val[fn]=s.insert({f.first+cur.first,f.second+cur.second,fn}).first;
    }
    cout<<(*s.begin()).first+ans;
    cout.flush();
    return 0;
}