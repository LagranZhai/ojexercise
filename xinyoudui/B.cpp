//PB
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=2e4;
struct Wood{
    int l{},w{};
}woods[maxn];
int n;
int dp[maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>woods[i].l>>woods[i].w;
    }
    std::sort(woods+1,woods+n+1,[](const Wood &A,const Wood &B){
        if(A.l==B.l){
            return A.w>B.w;
        }
        return A.l>B.l;
    });
    int ans{0};
    for(int i{1};i<=n;i++){
            // cout<<woods[i].w<<" ";
        for(int j{0};j<i;j++){
            if(woods[i].w>woods[j].w)dp[i]=std::max(dp[i],dp[j]+1);
        }
        ans=std::max(ans,dp[i]);
    }
    // cout<<"\n";
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}