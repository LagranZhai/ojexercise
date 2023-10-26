#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5,maxm=5e5;
int n,m,downtown;
int dfn[maxn+10],low[maxn+10],idx=0,scci[maxn+10]
    ,scccnt=0,scca[maxn+10],ind[maxn+10]
    ,dp[maxn+10];
bool sccisend[maxn+10];
stack<int > s;
struct Edge{
    int u,v,nxt,w;
};
struct Graph{
    int head[maxn+10],cnt=0,a[maxn+10];
    Edge edg[maxm+10];
    bool isend[maxn+10];
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
            else if(!scci[to]){
                low[x]=min(low[x],low[to]);
            }
        }
        if(dfn[x]==low[x]){
            ++scccnt;
            while(1){
                scci[s.top()]=scccnt;
                scca[scccnt]+=a[s.top()];
                sccisend[scccnt]|=isend[s.top()];
                if(s.top()==x){
                    s.pop();
                    break;
                }
                s.pop();
            }
        }
    }
    void topo(){
        queue<int > q;
        q.push(scci[downtown]);
        dp[scci[downtown]]=a[scci[downtown]];
        while(!q.empty()){
            int p=q.front();
            q.pop();
            for(int e=head[p];e;e=edg[e].nxt){
                int to=edg[e].v;
                if(dp[to]<dp[p]+a[to]){
                    dp[to]=dp[p]+a[to];
                    q.push(to);
                }
            }
        }
    }
}graph1,graph2;
int main(){
    //freopen("P3627_2.in","r",stdin);
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int u,v;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        graph1.addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        cin>>graph1.a[i];
    }
    int p;
    cin>>downtown>>p;
    int t;
    for(int i=1;i<=p;i++){
        cin>>t;
        graph1.isend[t]=1;
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])graph1.tarjan_scc(i,i);
    }
    for(int i=1;i<=graph1.cnt;i++){
        int u=graph1.edg[i].u;
        int v=graph1.edg[i].v;
        if(scci[u]!=scci[v]){
            graph2.addedge(scci[u],scci[v]);
            ind[scci[v]]++;
        }
    }
    for(int i=1;i<=scccnt;i++){
        graph2.a[i]=scca[i];
        graph2.isend[i]=sccisend[i];
    }
    graph2.topo();
    int ans=0;
    for(int i=1;i<=scccnt;i++){
        if(graph2.isend[i]){
            ans=max(ans,dp[i]);
        }
    }
    cout<<ans<<endl;
    return 0;
}