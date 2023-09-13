#include<iostream>
#include<algorithm>
#include<vector>
using std::cin,std::cout,std::ios,std::max;
constexpr int maxm=1e3;
int dp[maxm+100];
int n,m,R;
struct tim{
    int l,r,eff;
}t[maxm+100];
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>R;
    for(int i{1};i<=m;i++){
        cin>>t[i].l>>t[i].r>>t[i].eff;
    }
    int lp=0;
    std::sort(t+1,t+m+1,[](tim a,tim b){if(a.l==b.l)return a.r<b.r;return a.l<b.l;});
    
    for(int i{1};i<=m;i++){
        // while(lp+1<=m&&t[lp+1].r+R<=t[i].l)lp=lp+1;
        
        dp[i]=max(dp[i-1],dp[lp]+t[i].eff);
    }
    cout<<dp[m]<<"\n";
    return 0;
}