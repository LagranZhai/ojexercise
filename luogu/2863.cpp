#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4,maxm=1e5;
int n,m;
int head[maxn*2],cnt=1;
int low[maxn*2],dfn[maxn*2],idx=0,scc[maxn*2],scccnt=0;
stack<int > s;
struct Edge{
    int u=0,v=0,nxt=0;
}edge[maxm*2];
void addedge(int u,int v){
    edge[++cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].nxt=head[u];
    head[u]=cnt;
}
void tarjan(int x,int fa){
    s.push(x);
    low[x]=dfn[x]=++idx;
    for(int e=head[x];e;e=edge[e].nxt){
        int to=edge[e].v;
        if(!dfn[to]){
            tarjan(to,x);
            low[x]=min(low[x],low[to]);
        }
        else if(!scc[to]){
            low[x]=min(low[x],dfn[to]);
        }
    }
    if(low[x]==dfn[x]){
        int num=0;
        while(1){
            scc[s.top()]=x;
            num++;
            if(s.top()==x){
                s.pop();
                break;
            }
            s.pop();
        }
        if(num>1){
            scccnt++;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int u,v;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,i);
        }
    }
    cout<<scccnt<<endl;
    return 0;
}