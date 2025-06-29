//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=65;
int dp[maxn][maxn];
int G[maxn];
int r,b,g,m,p,n;
int vis[maxn];
int dfs(int x){
    if(vis[x])return 0;
    vis[x]=1;
    return 1+dfs(G[x]);
}
int qpow(int a,int b){
    int c{1};
    while(b){
        if(b&1)c=c*a%p;
        a=a*a%p;
        b>>=1;
    }
    return c;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>r>>b>>g>>m>>p;
    n=r+b+g;
    int ans{0};
    for(int i{1};i<=m;i++){
        for(int j{1};j<=n;j++){
            cin>>G[j];
            vis[j]=0;
        }
        std::vector<int> per;
        for(int j{1};j<=n;j++){
            if(!vis[j])per.push_back(dfs(j));
        }
        std::fill(dp[0],dp[0]+maxn*maxn,0);
        dp[0][0]=1;
        for(int a:per){
            for(int x{r};x>=0;x--){
                for(int y{b};y>=0;y--){
                    if(n-r-b>g)continue;
                    if(n-r-b<a)dp[x][y]=0;
                    if(x>=a)dp[x][y]=(dp[x][y]+dp[x-a][y])%p;
                    if(y>=a)dp[x][y]=(dp[x][y]+dp[x][y-a])%p;
                }
            }
        }
        ans=(ans+dp[r][b])%p;
    }
    for(int i{1};i<=n;i++){
        G[i]=i;vis[i]=0;
    }
    std::vector<int> per;
    for(int j{1};j<=n;j++){
        if(!vis[j])per.push_back(dfs(j));
    }
    std::fill(dp[0],dp[0]+maxn*maxn,0);
    dp[0][0]=1;
    for(int a:per){
        for(int x{r};x>=0;x--){
            for(int y{b};y>=0;y--){
                if(n-r-b>g)continue;
                if(n-r-b<a)dp[x][y]=0;
                if(x>=a)dp[x][y]=(dp[x][y]+dp[x-a][y])%p;
                if(y>=a)dp[x][y]=(dp[x][y]+dp[x][y-a])%p;
            }
        }
    }
    ans=(ans+dp[r][b])%p;
    cout<<ans*qpow(m+1,p-2)%p<<"\n";
    cout.flush();
    return 0;
}