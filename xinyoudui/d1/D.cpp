//PD
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=2e6;
int a[maxn],s[maxn];
int dp[maxn];
int n{0};
bool check(int x){
    std::deque<int> q;
    q.push_back(0);
    for(int i{1};i<=n;i++){
        while(!q.empty()&&s[i-1]-s[q.front()]>x)q.pop_front();
        if(q.empty()){
            std::fill(dp,dp+n,0);
            return false;
        }
        dp[i]=dp[q.front()]+a[i];
        while(!q.empty()&&dp[q.back()]>dp[i])q.pop_back();
        q.push_back(i);
    }
    int res{std::numeric_limits<int>::max()};
    for(int i{n};i>=0;i--){
        if(s[n]-s[i]<=x){
            res=std::min(res,dp[i]);
        }
        else{
            break;
        }
    }
    std::fill(dp,dp+n,0);
    return res<=x;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i{1};i<=n;i++){
            cin>>a[i];
            s[i]=s[i-1]+a[i];
        }
        int l{0},r{s[n]},mid;
        while(l<r){
            mid=(l+r)/2;
            if(check(mid)){
                r=mid;
            }
            else{
                l=mid+1;
            }
        }
        cout<<l<<"\n";        
        std::fill(a,a+n,0);
        std::fill(s,s+n,0);
    }
    cout.flush();
    return 0;
}