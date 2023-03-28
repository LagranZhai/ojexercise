#include<bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
const int maxn=1e3,maxm=30;
int dp[maxm][maxn*2];
int c[maxn*2];
int n,m;
void dijkstra(){
    set<pii> q;
    q.push(0,)
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int s;
    for(int i=1;i<=m;i++){
        cin>>c[i];
        if(c[i]==0){
            s=i;
        }
    }
    for(int i=1;i<=maxm-1;i++){
        for(int j=1;j<=maxn-1;j++){
            dp[i][j]=1e9;
        }
    }
    dp[s][1]=0;
    // for(int j=1;j<=n;j++){
    //     for(int i=1;i<=m;i++){
    //         if(i+1<=m&&j+c[i+1]<=n&&j+c[i+1]>=1){
    //         dp[i+1][j+c[i+1]]=min(dp[i+1][j+c[i+1]],dp[i][j]+2*abs(c[i+1])+1);
    //         }
    //         if(i-1>=1&&j+c[i-1]<=n&&j+c[i-1]>=1){
    //         dp[i-1][j+c[i-1]]=min(dp[i-1][j+c[i-1]],dp[i][j]+2*abs(c[i-1])+1);
    //         }
    //         if(j+c[i]<=n&&j+c[i]>=1){
    //         dp[i][j+c[i]]=min(dp[i][j+c[i]],dp[i][j]+2*abs(c[i]));
    //         }
    //     }
    // }
    queue<pii > q;
    q.push(make_pair(s,1));
    dp[s][1]=0;
    int num=0;
    while(!q.empty()){
        //num++;
        pii p=q.front();
        int i=p.first,j=p.second;
        q.pop();
        if(i+1<=m&&j+c[i+1]<=n&&j+c[i+1]>=1&&dp[i+1][j+c[i+1]]>dp[i][j]+2*abs(c[i+1])+1){
            dp[i+1][j+c[i+1]]=dp[i][j]+2*abs(c[i+1])+1;
            q.push(make_pair(i+1,j+c[i+1]));
        }
        if(i-1>=1&&j+c[i-1]<=n&&j+c[i-1]>=1&&dp[i-1][j+c[i-1]]>dp[i][j]+2*abs(c[i-1])+1){
            dp[i-1][j+c[i-1]]=dp[i][j]+2*abs(c[i-1])+1;
            q.push(make_pair(i-1,j+c[i-1]));
        }
        if(j+c[i]<=n&&j+c[i]>=1&&dp[i][j+c[i]]>dp[i][j]+2*abs(c[i])){
            dp[i][j+c[i]]=dp[i][j]+2*abs(c[i]);
            q.push(make_pair(i,j+c[i]));
        }
    }
    int ans=1e9;
    for(int i=1;i<=m;i++){
        ans=min(ans,dp[i][n]);
    }
    cout<<ans<<endl;
    return 0;
}