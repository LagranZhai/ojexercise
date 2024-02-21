//PD
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=500,maxm=1e5;
const int inf{std::numeric_limits<int>::max()};
int n,m;
int e[maxn][maxn],ans[maxn][maxn];
using pii=std::pair<int,int>;
pii c[maxn];
int val[maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int u,v,w;
    std::fill(e[0],e[0]+maxn*maxn,inf);
    std::fill(ans[0],ans[0]+maxn*maxn,inf);
    for(int i{};i<n;i++){
        cin>>w;val[i+1]=w;
        c[i+1]={w,i+1};
    }
    for(int i{};i<m;i++){
        cin>>u>>v>>w;
        e[u][v]=std::min(e[u][v],w);e[v][u]=std::min(e[v][u],w);
    }
    for(int i{1};i<=n;i++){
        e[i][i]=0;
    }
    std::sort(c+1,c+n+1);
    for(int i{1};i<=n;i++){
        int cur{c[i].second};
        for(int j{1};j<=n;j++){
            for(int k{1};k<=n;k++){
                if(e[j][cur]<inf&&e[cur][k]<inf&&e[j][k]>e[j][cur]+e[cur][k]){
                    e[j][k]=e[j][cur]+e[cur][k];
                }
            }
        }
        for(int j{1};j<=n;j++){
            for(int k{1};k<=n;k++){
                if(val[j]<=c[i].first&&val[k]<=c[i].first&&e[j][k]<inf){
                    ans[j][k]=std::min(ans[j][k],e[j][k]+c[i].first);
                }
            }
        }
    }
    int q;cin>>q;
    for(int i{};i<q;i++){
        cin>>u>>v;
        cout<<ans[u][v]<<"\n";
    }
    cout.flush();
    return 0;
}