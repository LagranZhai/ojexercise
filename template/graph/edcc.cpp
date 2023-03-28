//luogu8436
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5,maxm=2e6;
int n,m;
int head[maxn*2],cnt=1;//very improtant:fanbian ^ xiangdeng
int low[maxn*2],dfn[maxn*2],cur=0,edcccnt=0,dfx[maxn*2];
vector<int > edcc[maxn];
stack<int > s;
struct Edge{
    int u=0,v=0,nxt=0;
}edge[maxm*2+100],edge1[maxm*2+100];
void addedge(int u,int v){
    edge[++cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].nxt=head[u];
    head[u]=cnt;
}
void tarjan(int x,int fe){
    s.push(x);
    low[x]=dfn[x]=++cur;
    dfx[dfn[x]]=x;
    //cout<<"dfn"<<cur<<":"<<x<<endl;
    for(int e=head[x];e;e=edge[e].nxt){
        int to=edge[e].v;
        if(!dfn[to]){
            tarjan(to,e);
            low[x]=min(low[x],low[to]);
        }
        else if(e!=(fe^1)){//fe cant be fanbian of e(chongbian may exist)
            low[x]=min(low[x],dfn[to]);
        }
    }
    if(low[x]==dfn[x]){
        //cout<<"edccrt"<<x<<endl;
        ++edcccnt;
        while(1){
            edcc[edcccnt].push_back(s.top());
            if(s.top()==x){
                s.pop();
                break;
            }
            s.pop();
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
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,cnt+100);//never conflict
        }
    }
    //for(int i=1;i<=cur;i++)cout<<dfx[i]<<' ';
    cout<<edcccnt<<'\n';
    for(int i=1;i<=edcccnt;i++){
        cout<<edcc[i].size()<<' ';
        for(int u:edcc[i])cout<<u<<' ';
        cout<<'\n';
    }
    cout.flush();
    return 0;
}