#include<bits/stdc++.h>
using namespace std;
using ll=int;
const int maxm=2e6,maxn=3e3;
int n=0,m=0,s,t;
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
    int a,b,sum=0;
    cin>>a;
    n+=2+a;
    int w;
    for(int i=1;i<=a;i++){
        cin>>w;
        sum+=w;
        addedge(1,i+1,w);
    }
    for(int i=1;i<=a;i++){
        cin>>w;
        sum+=w;
        addedge(i+1,0,w);
    }
    m+=4*a;
    cin>>b;
    int k,c1,c2,u;
    for(int i=1;i<=b;i++){
        vector<int> uv;
        cin>>k;
        m+=4*k+4;
        cin>>c1>>c2;
        sum+=c1+c2;
        addedge(1,++n,c1);
        for(int j=1;j<=k;j++){
            cin>>u;
            uv.push_back(u);
            addedge(n,u+1,numeric_limits<ll>::max());
        }
        addedge(++n,0,c2);
        for(int j=1;j<=k;j++){
            u=uv[j-1];
            addedge(u+1,n,numeric_limits<ll>::max());
        }
    }
    s=1;t=0;
    cout<<sum-dinic()<<endl;
    return 0;
}