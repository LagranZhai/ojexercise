#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e6;
#define int long long
int a,b,c;
int n;
int sum[maxn*2];
struct Vec{
    int dx,dy;
};
int cross(Vec a,Vec b){
    return a.dx*b.dy-a.dy*b.dx;
}
struct Node{
    int x,y;
    Vec k;
};
int dp[maxn*2];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>a>>b>>c;
    for(int i{1};i<=n;i++){
        cin>>sum[i];
    }
    for(int i{1};i<=n;i++){
        sum[i]+=sum[i-1];
    }
    std::deque<Node> q;
    q.push_back({0,0,{1,1000000000ll}});
    for(int i{1};i<=n;i++){
        while(q.size()>1&&cross(q[1].k,{1,2*a*sum[i]})<=0)q.pop_front();
        dp[i]=q.front().y-2*a*sum[i]*q.front().x+a*sum[i]*sum[i]+b*sum[i]+c;
        Node cur{sum[i],dp[i]-b*sum[i]+a*sum[i]*sum[i],{0,0}};
        while(1){
            cur.k={cur.x-q.back().x,cur.y-q.back().y};
            if(q.size()>1&&cross(q.back().k,cur.k)>0)q.pop_back();
            else break;
        }
        q.push_back(cur);
    }
    cout<<dp[n]<<"\n";
    cout.flush();
    return 0;
}