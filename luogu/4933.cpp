#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3;
const int maxv=2e4;
const int P=998244353;
int h[maxn];
int dp[maxn][maxv*3];
int main(){
    ios::sync_with_stdio(false);
    int n,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>h[i];
    for(int i=1;i<=n;i++){
        for(int v=0;v<maxv*3;v++){
            dp[i][v]=1;
       }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            dp[i][h[i]-h[j]+maxv]+=dp[j][h[i]-h[j]+maxv];
            dp[i][h[i]-h[j]+maxv]%=P;
            ans+=dp[j][h[i]-h[j]+maxv];ans%=P;
        }
        ans++;ans%=P;
    }
    cout<<ans<<endl;
    cout.flush();
    return 0;
}