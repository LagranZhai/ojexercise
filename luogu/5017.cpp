#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxt=5e6;
int n,m;
int cnt[maxt],sum[maxt];
int mt{0};
struct Vec{
    int dx,dy;
};
struct Node{
    int x,y;
    Vec v;
};
// constexpr double eps=-1e-14;
int dp[maxt*2];
int cross(Vec x,Vec y){
    return x.dx*y.dy-y.dx*x.dy;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    std::fill(dp,dp+maxt*2,std::numeric_limits<int>::max());
    cin>>n>>m;
    int t;
    for(int i{1};i<=n;i++){
        cin>>t;
        mt=std::max(mt,t);
        cnt[t]++;
    }
    for(int i{0};i<=mt+m;i++){
        sum[i]=sum[i-1]+cnt[i]*i;
    }
    for(int i{0};i<=mt+m;i++){
        cnt[i]+=cnt[i-1];
    }
    std::deque<Node> q;
    q.push_back({0,0,{1,-maxt}});
    for(int i{0};i<=mt+m;i++){
        // if(i==10){
        //     cout<<"a";
        // } 
        if(i-m>=0){
            Node cur{cnt[i-m],dp[i-m]+sum[i-m],{}};
            while(q.size()>1&&cross({cur.x-q.back().x,cur.y-q.back().y},q.back().v)>=0)q.pop_back();
            cur.v={cur.x-q.back().x,cur.y-q.back().y};
            q.push_back(cur);
        }
        // if(cnt[i]>cnt[i-1]){
            while(q.size()>1&&cross({1,i},q[1].v)<0)q.pop_front();
            dp[i]=q.front().y+cnt[i]*i-sum[i]-q.front().x*i;
        // }
    }
    int ans{std::numeric_limits<int>::max()};
    for(int i{mt};i<=mt+m;i++){
        ans=std::min(ans,dp[i]);
    }
    cout<<ans<<"\n";
    // for(int i{0};i<=mt+m;i++){
    //     cout<<i<<" "<<dp[i]<<"\n";
    // }
    cout.flush();
    return 0;
}