#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4;
const int maxm=1e5;
int head[maxn],cnt=0,n=0;
struct Edge{
    int to,nxt;
}edg[maxm];
void addedge(int u,int v){
    edg[++cnt].to=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    return;
}
int tim[maxn],ind[maxn],dp[maxn];
void topo(){
    queue<int > q;
    for(int i=1;i<=n;i++){
        if(ind[i]==0){
            q.push(i);
            dp[i]=tim[i];
        }
    }
    while(!q.empty()){
        int p=q.front();
        q.pop();
        for(int e=head[p];e;e=edg[e].nxt){
            ind[edg[e].to]--;
            dp[edg[e].to]=max(dp[edg[e].to],dp[p]+tim[edg[e].to]);
            if(ind[edg[e].to]==0)q.push(edg[e].to);
        }
    }
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    int x,u;
    for(int i=1;i<=n;i++){
        cin>>x;
        cin>>tim[x];
        while(cin>>u){
            if(u==0)break;
            addedge(u,x);
            ind[x]++;
        }
    }
    topo();
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;

    return 0;
}