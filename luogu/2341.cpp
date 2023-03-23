#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5,maxm=5e5;
int n,m;
int dfn[maxn+100],low[maxn+100],idx;
int sccrt[maxn+100],scccnt=0;
vector<int > scc[maxn+100];
int ind[maxn+100],outd[maxn+100];
struct Edge{
    int u=0,v=0,nxt=0;
};
stack<int > s;
struct Graph{
    int head[maxn+100],cnt=0;
    Edge edg[maxm+100];
    void addedge(int u,int v){
        edg[++cnt].u=u;
        edg[cnt].v=v;
        edg[cnt].nxt=head[u];
        head[u]=cnt;
    }
    void tarjan_scc(int x,int fa){
        s.push(x);
        dfn[x]=low[x]=++idx;
        for(int e=head[x];e;e=edg[e].nxt){
            int to=edg[e].v;
            if(!dfn[to]){
                tarjan_scc(to,x);
                low[x]=min(low[x],low[to]);
            }
            else if(!sccrt[to]){
                low[x]=min(low[x],dfn[to]);
            }
        }
        if(low[x]==dfn[x]){
            ++scccnt;
            while(1){
                sccrt[s.top()]=scccnt;
                scc[scccnt].push_back(s.top());
                if(s.top()==x){
                    s.pop();
                    break;
                }
                s.pop();
            }
        }
    }
}graph1,graph2;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int u,v;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        if(u!=v)graph1.addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            graph1.tarjan_scc(i,i);
        }
    }
    for(int i=1;i<=graph1.cnt;i++){
        int u=graph1.edg[i].u;
        int v=graph1.edg[i].v;
        if(sccrt[u]!=sccrt[v]){
            //graph2.addedge(sccrt[u],sccrt[v]);
            ind[sccrt[v]]++;
            outd[sccrt[u]]++;
        }
    }
    int num=0,mx;
    for(int i=1;i<=scccnt;i++){
        if(!outd[i]){
            num++;
            mx=i;
        }
    }
    if(num>1||num==0){
        cout<<0<<endl;
    }
    else{
        cout<<scc[mx].size()<<endl;
    }
    return 0;
}