#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=5e3;
int a[maxn+10][maxn+10];
int n,m;
bool vis[maxn*2];
int dis[maxn*2];
// std::vector<int > t;
int prim(){
    int res=0;
    for(int i{1};i<=n;i++){
        // t.push_back(i);
        dis[i]=std::numeric_limits<int >::max();
    }
    vis[1]=1;
    dis[1]=0;
    int tot=1;
    for(int i{1};i<=n;i++){
        dis[i]=std::min(dis[i],a[1][i]);
    }
    while(tot<n){
        int minx=0,mindis=std::numeric_limits<int >::max();
        for(int i{1};i<=n;i++){
            if(dis[i]<mindis&&vis[i]==0){
                minx=i;
                mindis=dis[i];
            }
        }
        // std::cerr<<mindis;
        if(mindis==std::numeric_limits<int >::max()){
            // std::cerr<<tot;
            return 0;
        }
        res+=mindis;
        vis[minx]=1;
        for(int i{1};i<=n;i++){
            if(a[minx][i]<std::numeric_limits<int >::max()&&vis[i]==0){
                dis[i]=std::min(dis[i],a[minx][i]);
            }
        }
        tot++;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int x,y,z;
    for(int i{1};i<=n;i++){
        for(int j{1};j<=n;j++){
            if(i!=j){
                a[i][j]=std::numeric_limits<int >::max();
            }
            else{
                a[i][j]=0;
            }
        }
    }
    for(int i{1};i<=m;i++){
        cin>>x>>y>>z;
        a[x][y]=std::min(a[x][y],z);
        a[y][x]=std::min(a[y][x],z);
    }
    int ans=prim();
    if(ans){
        cout<<ans<<std::endl;
    }
    else{
        cout<<"orz"<<std::endl;
    }
    // cout<<ans<<std::endl;
    return 0;
}