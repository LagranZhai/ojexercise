#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3,maxm=1e5;
int head[maxn*2],cnt=0;
int a[maxn*2];
struct Edge{
    int u,v,nxt;
}edge[maxm*2];
void addedge(int u,int v){
    edge[++cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].nxt=head[u];
    head[u]=cnt;
}
int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int u,v;
    for(int i=1;i<=m;i++){
        addedge(u,v);
    }
    return 0;
}