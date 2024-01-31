#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=1e4,maxm=1e5;
#define int long long
struct Edge{
    int v,nxt;
}edg[maxm*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int n,m;
std::priority_queue<int,std::vector<int> ,std::greater<int> > scc[maxn*2];
int scccnt{0},scci[maxn*2];
int dfn[maxn*2],low[maxn*2],idx{0};
std::stack<int> s;
void tarjan(int x){
    s.push(x);
    dfn[x]=low[x]=++idx;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(!dfn[to]){
            tarjan(to);
            low[x]=std::min(low[x],low[to]);
        }
        else if(!scci[to]){
            low[x]=std::min(low[x],dfn[to]);
        }
    }
    if(dfn[x]==low[x]){
        scccnt++;
        while(1){
            scc[scccnt].push(s.top());
            scci[s.top()]=scccnt;
            if(s.top()==x){
                s.pop();
                break;
            }
            s.pop();
        }
    }
}
bool out[maxn*2];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int u,v;
    for(int i{1};i<=m;i++){
        cin>>u>>v;
        if(u!=v){
            addedge(u,v);
        }
    }
    for(int i{1};i<=n;i++){
        if(!scci[i]){
            tarjan(i);
        }
    }
    cout<<scccnt<<"\n";
    for(int i{1};i<=n;i++){
        if(!out[scci[i]]){
            out[scci[i]]=1;
            while(!scc[scci[i]].empty()){
                cout<<scc[scci[i]].top()<<" ";
                scc[scci[i]].pop();
            }
            cout<<"\n";
        }
    }
    cout.flush();
    return 0;
}