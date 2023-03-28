//luogu8435
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5,maxm=2e6;
int n,m;
int head[maxn+100],cnt=0;
stack<int > s;
int dfn[maxn+100],low[maxn+100],idx=0;
int vdcccnt=0;vector<int > vdcc[maxn];
struct Edge{
    int v=0,nxt=0;
}edg[maxm*2+100];
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
}
void tarjan(int x,int fa){
    s.push(x);
    dfn[x]=low[x]=++idx;
    int child=0;
    for(int e=head[x];e;e=edg[e].nxt){
        int to=edg[e].v;
        if(!dfn[to]){
            child++;
            tarjan(to,x);
            low[x]=min(low[x],low[to]);
            if(low[to]>=dfn[x]){
                ++vdcccnt;
                while(1){
                    vdcc[vdcccnt].push_back(s.top());
                    if(s.top()==to){
                        s.pop();
                        break;
                    }
                    s.pop();
                }
                vdcc[vdcccnt].push_back(x);
            }
        }
        else if(to!=fa){
            low[x]=min(low[x],dfn[to]);
        }
    }
    if(fa==0&&child==0)vdcc[++vdcccnt].push_back(x);
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int u,v;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
        }
    }
    cout<<vdcccnt<<'\n';
    for(int i=1;i<=vdcccnt;i++){
        cout<<vdcc[i].size()<<' ';
        for(int u:vdcc[i])cout<<u<<' ';
        cout<<'\n';
    }
    cout.flush();
    return 0;
}