#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxm=2000,maxn=26;
int ins[300],del[300];
int n,m;
std::string s;
int dp[maxm+100][maxm+100];
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    cin>>s;
    char a;
    for(int i{1};i<=n;i++){
        cin>>a;
        cin>>ins[a]>>del[a];
    }
    for(int l{2};l<=m;l++){
        for(int i{0};i+l-1<m;i++){
            if(s[i]==s[i+l-1]){
                if(l==2)dp[i][i+l-1]=0;
                else dp[i][i+l-1]=dp[i+1][i+l-2];
            }
            else{
                dp[i][i+l-1]=std::min({dp[i+1][i+l-1]+ins[s[i]],dp[i+1][i+l-1]+del[s[i]],
                                        dp[i][i+l-2]+del[s[i+l-1]],dp[i][i+l-2]+ins[s[i+l-1]]});
            }
        }
    }
    cout<<dp[0][m-1]<<std::endl;
    return 0;
}