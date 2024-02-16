//PB
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=100;
int dp[maxn][maxn];
std::string s,t;
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>s>>t;
    dp[0][0]=1;
    for(int i{1};i<=s.size();i++){
        dp[i][0]=1;
        for(int j{1};j<=t.size();j++){
            if(s[i-1]==t[j-1]){
                dp[i][j]+=dp[i-1][j-1];
            }
            dp[i][j]+=dp[i-1][j];
        }
    }
    cout<<dp[s.size()][t.size()]<<"\n";
    cout.flush();
    return 0;
}