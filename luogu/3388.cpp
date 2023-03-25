#include<bits/stdc++.h>
using namespace std;
const int maxn=2e4,maxm=1e5;
int head[maxn+100],cnt=0,dfn[maxn+100],low[maxn+100],cur=0;
bool cut[maxn+100];
struct Edge{
    int to,nxt;
}edg[maxm*3];
void addedge(int u,int v){
    edg[++cnt].to=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    edg[++cnt].to=u;
    edg[cnt].nxt=head[v];
    head[v]=cnt;
    return;
}
void tarjan(int x,int fa){
    dfn[x]=low[x]=++cur;
    int child=0;
    for(int e=head[x];e;e=edg[e].nxt){
        int to=edg[e].to;
        if(dfn[to]==0){
            child++;
            tarjan(to,x);
            low[x]=min(low[x],low[to]);
            if(low[to]>=dfn[x]&&x!=fa){
                cut[x]=1;
            }
        }
        else if(dfn[to]<dfn[x]&&to!=fa){
            low[x]=min(low[x],dfn[to]);
        }
    }
    if(x==fa&&child>=2){
        cut[x]=1;
    }
}
int main(){
    ios::sync_with_stdio(false);
    int n,m;
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
    int ansn=0;vector<int> ans;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            ansn++;
            ans.push_back(i);
        }
    }
    cout<<ansn<<'\n';
    for(auto i:ans)cout<<i<<' ';
    cout.flush();
    return 0;
}