#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5,logw=32;
int dp[logw];
int a[maxn+100];
int n;
int main(){
    cin.tie(0)->sync_with_stdio(false);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    for(int i{1};i<=n;i++){
        int cur{a[i]},cnt{0};
        int res{0};
        while(cur>0){
            if(cur&1){
                res=std::max(res,dp[cnt]+1);
            }
            cnt++;
            cur>>=1;
        }
        cnt=0;cur=a[i];
        while(cur>0){
            if(cur&1){
                dp[cnt]=std::max(res,dp[cnt]);
            }
            cnt++;
            cur>>=1;
        }
    }
    int ans{0};
    for(int i{0};i<logw;i++){
        ans=std::max(ans,dp[i]);
    }
    cout<<ans<<"\n";
    cout<<std::flush;
    return 0;
}