#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=5e3;
#define int long long
int near[maxn+10];
int x[maxn+10],y[maxn+10];
int n;
int a[maxn+10][maxn+10];
int dis[maxn+10];
bool vis[maxn+10];
int prim(){
    int res=0;
    for(int i{1};i<=n;i++){
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
        res=std::max(res,mindis);
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
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>x[i]>>y[i];
    }
    int maxnear=0;
    for(int i{1};i<=n;i++){
        // near[i]=std::numeric_limits<long long >::max();
        for(int j{1};j<=n;j++){
                a[i][j]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
        // maxnear=std::max(maxnear,near[i]);
        }
    }
    cout<<prim()<<std::endl;
    return 0;
}