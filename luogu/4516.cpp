#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5,maxk=100;
constexpr int P=1e9+7;
struct Edge{
    int nxt{0},v{0};
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
}
int n,k;
int dp[maxn+10][maxk+10][2][2];
int siz[maxn*2];
int tmp[maxk+10][2][2];
void dfs(int x,int f){
    dp[x][0][0][0]=1;dp[x][1][1][0]=1;
    siz[x]=1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x);
            for(int i{0};i<=std::min(siz[x],k);i++){
                tmp[i][0][1]=dp[x][i][0][1];dp[x][i][0][1]=0;
                tmp[i][0][0]=dp[x][i][0][0];dp[x][i][0][0]=0;
                tmp[i][1][1]=dp[x][i][1][1];dp[x][i][1][1]=0;
                tmp[i][1][0]=dp[x][i][1][0];dp[x][i][1][0]=0;
            }
            for(int i{0};i<=std::min(k,siz[x]);i++){
                for(int j{0};j<=std::min(k-i,siz[to]);j++){
                    dp[x][i+j][0][0]=(0ll+dp[x][i+j][0][0]+1ll*tmp[i][0][0]*dp[to][j][0][1]%P)%P;
                    dp[x][i+j][0][1]=(((0ll+dp[x][i+j][0][1]+((0ll+tmp[i][0][0]+tmp[i][0][1])%P)*dp[to][j][1][1]%P)%P)+1ll*tmp[i][0][1]*dp[to][j][0][1]%P)%P;
                    dp[x][i+j][1][0]=(0ll+dp[x][i+j][1][0]+1ll*tmp[i][1][0]*((0ll+dp[to][j][0][1]+dp[to][j][0][0])%P)%P)%P;
                    dp[x][i+j][1][1]=(0ll+(0ll+dp[x][i+j][1][1]+((0ll+tmp[i][1][1]+tmp[i][1][0])%P)*((0ll+dp[to][j][1][0]+dp[to][j][1][1])%P)%P)%P+(tmp[i][1][1])*((0ll+dp[to][j][0][0]+dp[to][j][0][1])%P)%P)%P;
                }
            }
            siz[x]+=siz[to];
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
    dfs(1,0);
    cout<<dp[1][k][0][1]+dp[1][k][1][1]<<"\n";
    cout.flush();
    return 0;
}