#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=1e4;   
ll a[maxn],dp[maxn][maxn];
int main(){
    ios::sync_with_stdio(false);
    int n,w,s;
    cin>>n>>w>>s;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=w+s-1;j++){
            dp[i][j]=max(dp[i-1][j-1>w?w:j-1]+a[i]*j,dp[i][j-1]+a[i]*j);
        }
    }
    cout.flush();
    return 0;
}