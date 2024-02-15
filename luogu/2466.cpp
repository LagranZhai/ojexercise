#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e3;
#define int long long
int N,x0;
// int x[maxn*2],y[maxn*2],v[maxn*2];
int dp[maxn+10][maxn+10][2];
struct Node{
    int x,y,v;
}egg[maxn*2];
int sum[maxn*2];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>N>>x0;
    for(int i{1};i<=N;i++){
        cin>>egg[i].x;
    }
    for(int i{1};i<=N;i++){
        cin>>egg[i].y;
    }
    for(int i{1};i<=N;i++){
        cin>>egg[i].v;
    }
    egg[N+1]={x0,0,0};
    std::sort(egg+1,egg+N+2,[](const Node &A,const Node &B){return A.x<B.x;});
    std::fill(dp[0][0],dp[0][0]+(maxn+10)*(maxn+10)*2,std::numeric_limits<int>::max()>>2);
    int start{0},ans{0};
    for(int i{1};i<=N+1;i++){
        if(egg[i].x==x0&&egg[i].y==0&&egg[i].v==0){
            start=i;
        }
        sum[i]=sum[i-1]+egg[i].v;
        ans+=egg[i].y;
    }
    dp[start][start][1]=dp[start][start][0]=0;
    for(int l{2};l<=N+1;l++){
        for(int i{1};i+l-1<=N+1;i++){
            dp[i][i+l-1][0]=std::min(dp[i+1][i+l-1][0]+(egg[i+1].x-egg[i].x)*(sum[i]+sum[N+1]-sum[i+l-1]),dp[i+1][i+l-1][1]+(egg[i+l-1].x-egg[i].x)*(sum[i]+sum[N+1]-sum[i+l-1]));
            dp[i][i+l-1][1]=std::min(dp[i][i+l-2][1]+(egg[i+l-1].x-egg[i+l-2].x)*(sum[i-1]+sum[N+1]-sum[i+l-2]),dp[i][i+l-2][0]+(egg[i+l-1].x-egg[i].x)*(sum[i-1]+sum[N+1]-sum[i+l-2]));
        }
    }
    ans-=std::min(dp[1][N+1][0],dp[1][N+1][1]);
    cout<<std::fixed<<std::setprecision(3)<<(double)ans/1000.0<<"\n";
    cout.flush();
    return 0;
}