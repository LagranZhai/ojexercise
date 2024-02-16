//PB
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=30;
int n;
int tong[maxn];
std::set<int> ans;
int vis[maxn][maxn][maxn];
void dao(int to,int &x,int &y){
    if(tong[to]-y>x){
        y+=x;x=0;
    }
    else{
        x-=tong[to]-y;
        y=tong[to];
    }
}
void dfs(int x,int y,int z){
    if(vis[x][y][z])return ;
    vis[x][y][z]=1;
    if(x==0)ans.insert(z);
    int u,v;
    u=x;v=y;dao(2,u,v);
    dfs(u,v,z);
    u=y;v=x;dao(1,u,v);
    dfs(v,u,z);
    u=x;v=z;dao(3,u,v);
    dfs(u,y,v);
    u=z;v=x;dao(1,u,v);
    dfs(v,y,u);
    u=y;v=z;dao(3,u,v);
    dfs(x,u,v);
    u=z;v=y;dao(2,u,v);
    dfs(x,v,u);
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    // cin>>n;
    n=3;
    for(int i{1};i<=n;i++){
        cin>>tong[i];
    }
    dfs(0,0,tong[3]);
    for(auto a:ans){
        cout<<a<<"\n";
    }
    cout.flush();
    return 0;
}