#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5;
int head[maxn*2],cnt=0;
struct Edge{
    int v{0},nxt{0};
}edg[maxn*4];
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
}
int n,m;
int c[maxn*2];

bool dfs(int u,int f,int col){
    c[u]=col;
    for(int e{head[u]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            if(c[to]==col){
                return false;
            }
            else{
                if(c[to]==0){
                    if(!dfs(to,u,(col==1)?2:1)){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
int main(){
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        int u,v;
        for(int i{1};i<=m;i++){
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        if(dfs(1,0,1)){
            cout<<"YES\n";
        }
        else{
            cout<<"NO\n";
        }
        std::fill(head,head+n,0);
        std::fill(c,c+n,0);
        cnt=0;
    }
    cout.flush();
    return 0;
}