#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4,maxm=5e4;
int n;
int dfn[maxn+10],low[maxn+10],idx=0,scci[maxn+10]
    ,scccnt=0,ind[maxn+10],oud[maxn*2]
    ,dp[maxn+10];
int ccid[maxn*2];
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
    //freopen("P3627_2.in","r",stdin);
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++){
        int cur{1};
        while(cur!=0){
            cin>>cur;
            if(cur==0)break;
            graph1.addedge(i,cur);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])graph1.tarjan_scc(i,i);
    }
    for(int i=1;i<=graph1.cnt;i++){
        int u=graph1.edg[i].u;
        int v=graph1.edg[i].v;
        if(scci[u]!=scci[v]){
            graph2.addedge(scci[u],scci[v]);
            ind[scci[v]]++;oud[scci[u]]++;
        }
    }
    int ind0{0},oud0{0};
    for(int i{1};i<=scccnt;i++){
        if(ind[i]==0)ind0++;
        if(oud[i]==0)oud0++;
    }
    cout<<ind0<<"\n"<<((scccnt==1)?0:std::max(ind0,oud0))<<endl;
    return 0;
}