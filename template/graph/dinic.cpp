//P3376
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxm=5e3,maxn=200;
int n,m,s,t;
int head[maxn*3],cnt=1;
int dep[maxn*3],cur[maxn*3];
struct Edge{
    int to,nxt;
    ll w;
}edg[maxm*3];
void addedge(int u,int v,int w){
    edg[++cnt].w=w;
    edg[cnt].to=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    edg[++cnt].w=0;
    edg[cnt].to=u;
    edg[cnt].nxt=head[v];
    head[v]=cnt;
}
int bfs(){
    fill(begin(dep),end(dep),-1);
    dep[s]=0;
    copy(begin(head),end(head),begin(cur));
    queue<int > q;
    q.push(s);
    while(!q.empty()){
        int p=q.front();
        q.pop();
        for(int e=head[p];e;e=edg[e].nxt){
            int to=edg[e].to;
            ll w=edg[e].w;
            if(w>0ll&&dep[to]==-1){
                dep[to]=dep[p]+1;
                q.push(to);
            }
        }
    }
    return dep[t];
}
ll dfs(int p,ll flow){
    if(p==t)return flow;
    ll rf=flow;
    for(int e=cur[p];e&&rf;e=edg[e].nxt){
        cur[p]=e;
        int to=edg[e].to;
        ll w=edg[e].w;
        if(w>0&&dep[to]==dep[p]+1){
            ll c=dfs(to,min(w,rf));
            rf-=c;
            edg[e].w-=c;
            edg[e^1].w+=c;
        }
    }
    return flow-rf;
}
ll dinic(){
    ll ans=0;
    while(bfs()!=-1)ans+=dfs(s,numeric_limits<ll>::max());
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    int u,v,w;
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        addedge(u,v,w);
    }
    cout<<dinic()<<endl;
    return 0;
}