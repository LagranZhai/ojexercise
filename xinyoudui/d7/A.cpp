//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=300;
const int inf{std::numeric_limits<int>::max()};
int e[maxn][maxn],now[maxn][maxn];
bool flag[maxn];
int n,m;
void solve(int l,int r){
    if(l==r){
        for(int i{1};i<=n;i++){
            for(int j{1};j<=n;j++){
                if(now[i][j]!=e[i][j]){
                    flag[l]=1;
                }
            }
        }
        return;
    }
    int mid{(l+r)/2};
    int tmp[maxn][maxn];
    std::copy(now[0],now[0]+maxn*maxn,tmp[0]);
    for(int k{l};k<=mid;k++){
        for(int i{1};i<=n;i++){
            for(int j{1};j<=n;j++){
                if(now[i][k]!=inf&&now[k][j]!=inf&&now[i][j]>now[i][k]+now[k][j]){
                    now[i][j]=now[i][k]+now[k][j];
                }
            }
        }
    }
    solve(mid+1,r);
    std::copy(tmp[0],tmp[0]+maxn*maxn,now[0]);
    for(int k{mid+1};k<=r;k++){
        for(int i{1};i<=n;i++){
            for(int j{1};j<=n;j++){
                if(now[i][k]!=inf&&now[k][j]!=inf&&now[i][j]>now[i][k]+now[k][j]){
                    now[i][j]=now[i][k]+now[k][j];
                }
            }
        }
    }
    solve(l,mid);
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int u,v,w;
    std::fill(e[0],e[0]+maxn*maxn,std::numeric_limits<int>::max());
    std::fill(now[0],now[0]+maxn*maxn,std::numeric_limits<int>::max());
    for(int i{1};i<=m;i++){
        cin>>u>>v>>w;
        e[u][v]=w;e[v][u]=w;now[u][v]=w;now[v][u]=w;
    }
    for(int i{1};i<=n;i++)e[i][i]=0,now[i][i]=0;
    bool ex{0};
    for(int k{1};k<=n;k++){
        for(int i{1};i<=n;i++){
            for(int j{1};j<=n;j++){
                if(e[i][k]!=inf&&e[k][j]!=inf&&e[i][j]>e[i][k]+e[k][j]){
                    e[i][j]=e[i][k]+e[k][j];
                }
            }
        }
    }
    solve(1,n);
    for(int i{1};i<=n;i++){
        if(flag[i])ex=1;
    }
    if(ex){
        for(int i{1};i<=n;i++){
            if(flag[i])cout<<i<<" ";
        }
        cout<<"\n";
    }
    else{
        cout<<"No important cities.\n";
    }
    cout.flush();
    return 0;
}