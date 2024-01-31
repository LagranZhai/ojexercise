#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=200;
struct Edge{
    int v,nxt;
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int n;
int ans{0};
int dep[maxn*2];
std::queue<int> q[maxn*2];
void dfs(int x,int f){
    q[x].push(0);q[x].push(0);
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x);
            if(q[x].size()==2){
                q[x].pop();
                q[x].push()
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i{1};i<=n;i++){
        dep[0]=-1;
        dfs(i,0);
        for(int e{head[i]};e)
    }
    cout.flush();
    return 0;
}