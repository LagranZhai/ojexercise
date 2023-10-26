/*xtcakioi*/
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=500;
#define int long long
constexpr int p=998244353;
int dp[2][maxn+10][maxn+10];
int n;
std::string s;
inline bool chk(int l,int r){
    if((s[l]=='('||s[l]=='?')&&(s[r]==')'||s[r]=='?')){
        return true;
    }
    else return false;
}
void solve(int n){
    for(int l{2};l<=n;l++){
        for(int i{0};i+l-1<n;i++){
            if(l==2){
                if(chk(i,i+l-1)){
                    dp[0][i][i+l-1]=1;
                    dp[1][i][i+l-1]=1;
                }
            }
            else{
                if(chk(i,i+l-1)){
                    dp[1][i][i+l-1]=dp[0][i+1][i+l-2];
                    dp[0][i][i+l-1]=dp[0][i+1][i+l-2];
                }
                for(int j{i};j<i+l-1;j++){
                    dp[0][i][i+l-1]=(dp[1][i][j]*dp[0][j+1][i+l-1]%p+dp[0][i][i+l-1])%p;
                }
            }
        }
    }
    cout<<dp[0][0][n-1]<<std::endl;
    std::fill(dp[0][0],dp[0][0]+2*maxn*maxn,0);
}
signed main(){
    ios::sync_with_stdio(false);
    for(int n{1};n<=20;n++){
        s.clear();
        for(int j{1};j<=n;j++){
            s.push_back('?');
        }
        solve(n);
    }
    return 0;
}