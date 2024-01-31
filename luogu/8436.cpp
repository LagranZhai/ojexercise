#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=5e5,maxm=2e6;
#define int long long
int n,m;
struct Edge{
    int v,nxt;
}edg[maxm*3];
int head[maxn*2],cnt{1};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int dfn[maxn*2],low[maxn*2],idx{0};
std::vector<int> edcc[maxn*2];
int edcccnt{0},edcci[maxn*2];
std::stack<int> s;
void tarjan(int x,int fe){
    s.push(x);
    dfn[x]=low[x]=++idx;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(e==(fe^1))continue;
        if(!dfn[to]){
            tarjan(to,e);
            low[x]=std::min(low[x],low[to]);
        }
        else{
            low[x]=std::min(low[x],dfn[to]);
        }
    }
    if(low[x]==dfn[x]){
        edcccnt++;
        while(1){
            edcci[s.top()]=edcccnt;
            edcc[edcccnt].push_back(s.top());
            if(s.top()==x){
                s.pop();
                break;
            }
            s.pop();
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    int u,v;
    for(int i{1};i<=m;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i{1};i<=n;i++){
        if(!edcci[i]){
            tarjan(i,0);
        }
    }
    cout<<edcccnt<<"\n";
    for(int i{1};i<=edcccnt;i++){
        cout<<edcc[i].size()<<" ";
        for(auto e:edcc[i]){
            cout<<e<<" ";
        }
        cout<<"\n";
    }
    cout.flush();
    return 0;
}