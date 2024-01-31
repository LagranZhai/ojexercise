#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=100,maxm=5e3;
int dis[maxn+10][maxn+10];
int e[maxn+10][maxn+10];
int n,m;
int main(){
    ios::sync_with_stdio(false);
    std::fill(dis[0],dis[0]+(maxn+10)*(maxn+10),1e9+1);
    std::fill(e[0],e[0]+(maxn+10)*(maxn+10),1e9+1);
    cin>>n>>m;
{
    int u,v,w;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>w;
        dis[u][v]=std::min(dis[u][v],w);
        e[u][v]=std::min(e[u][v],w);
        dis[v][u]=std::min(dis[v][u],w);
        e[v][u]=std::min(e[v][u],w);
    }
}
    for(int i{1};i<=n;i++){
        dis[i][i]=0;
        e[i][i]=0;
    }
    int ans{std::numeric_limits<int>::max()};
    for(int k{1};k<=n;k++){
        for(int u{1};u<=n;u++){
            for(int v{1};v<=n;v++){
                if(dis[u][v]<=1e9&&e[k][v]<=1e9&&e[u][k]<=1e9&&u!=v&&u!=k&&v!=k)ans=std::min(ans,dis[u][v]+e[u][k]+e[k][v]);
                if(dis[k][v]<=1e9&&dis[u][k]<=1e9)dis[u][v]=std::min(dis[u][v],dis[u][k]+dis[k][v]);
            }
        }
    }
    if(ans<=1e9)cout<<ans<<"\n";
    else cout<<"No solution.\n";
    cout.flush();
    return 0;
}