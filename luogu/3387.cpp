#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4,maxm=1e5;
int n,m;
int head[maxn*2],cnt=0,head1[maxn*2],ind[maxn*2];
int low[maxn*2],dfn[maxn*2],cur=0,scc[maxn*2],nowcnt=0;
int a[maxn*2],dp[maxn*2];
stack<int > s;
struct Edge{
    int u=0,v=0,nxt=0;
}edge[maxm*2],edge1[maxm*2];
void addedge(int u,int v){
    edge[++cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].nxt=head[u];
    head[u]=cnt;
}
void addedge1(int u,int v){
    edge1[++nowcnt].u=u;
    edge1[nowcnt].v=v;
    edge1[nowcnt].nxt=head1[u];
    head1[u]=nowcnt;
}
void tarjan(int x,int fa){
    s.push(x);
    low[x]=dfn[x]=++cur;
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
        //++scccnt;
        while(1){
            scc[s.top()]=x; 
            if(s.top()==x){
                s.pop();
                break;
            }
            a[x]+=a[s.top()];
            s.pop();
        }
    }
}
void topo(){
    queue<int > q;
    for(int i=1;i<=n;i++){
        if(scc[i]==i&&ind[scc[i]]==0){
            q.push(i);
            dp[i]=a[i];
        }
    }
    while(!q.empty()){
        int cq=q.front();
        q.pop();
        for(int e=head1[cq];e;e=edge1[e].nxt){
            int to=edge1[e].v;
            dp[to]=max(dp[to],dp[cq]+a[to]);
            ind[to]--;
            if(ind[to]==0)q.push(to);
        }
    }
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int u,v;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            //cout<<"tarjan"<<i<<endl;
            tarjan(i,i);
        }
    }
    // for(int i=1;i<=n;i++){
    //     cout<<i<<"scc:"<<scc[i]<<endl;
    // }
    //cnt=0;
    //for(int i=1;i<=n;i++){
    for(int e=1;e<=cnt;e++){
        //Edge e=edge[i];
        int v=edge[e].v;
        int u=edge[e].u;
        if(scc[v]!=scc[u]){
            addedge1(scc[u],scc[v]);
            ind[scc[v]]++;
        }
    }
    //}
    topo();
    int ans=0;
    for(int i=1;i<=n;i++){
        if(scc[i]==i){
            ans=max(ans,dp[i]);
        }
    }
    cout<<ans<<'\n';
    return 0;
}