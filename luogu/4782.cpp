#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=2e6,maxm=2e6;
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
int dfn[maxn*2],low[maxn*2],idx{0};
std::vector<int> scc[maxn*2];
int scccnt{0},scci[maxn*2];
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
    if(low[x]==dfn[x]){
        scccnt++;
        while(1){
            scci[s.top()]=scccnt;
            scc[scccnt].push_back(s.top());
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
    int x,y;
    bool a,b;
    auto tonode{[](int a,bool b){
        return b?a:a+n;
    }};
    for(int i{1};i<=m;i++){
        cin>>x>>a>>y>>b;
        addedge(tonode(x,a^1),tonode(y,b));
        addedge(tonode(y,b^1),tonode(x,a));
    }
    for(int i{1};i<=2*n;i++){
        if(!scci[i]){
            tarjan(i);
        }
    }
    bool flag{0};
    for(int i{1};i<=n;i++){
        if(scci[i]==scci[i+n]){
            flag=1;
            break;
        }
    }
    if(flag){
        cout<<"IMPOSSIBLE\n";
    }
    else{
        cout<<"POSSIBLE\n";
        for(int i{1};i<=n;i++){
            if(scci[i]<scci[n+i]){
                cout<<1<<" ";
            }
            else{
                cout<<0<<" ";
            }
        }
    }
    cout.flush();
    return 0;
}