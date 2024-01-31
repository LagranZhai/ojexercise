#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5,maxp=100;
#define int long long
int n,m,p;
int d[maxn*2],h[maxn*2],t[maxn*2];
int g[maxn*2],gsum[maxn*2];
int dp[maxn*2][maxp+10];
struct Vec{
    int dx,dy;
};
int cross(Vec x,Vec y){
    return x.dx*y.dy-x.dy*y.dx;
}
struct Node{
    int x,y;
    Vec k;
};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>p;
    for(int i{2};i<=n;i++){
        cin>>d[i];
    }
    for(int i{2};i<=n;i++){
        d[i]+=d[i-1];
    }
    for(int i{1};i<=m;i++){
        cin>>h[i]>>t[i];
        g[i]=d[h[i]]-t[i];
    }
    std::deque<Node> q[maxp+10];
    for(int i{0};i<=p;i++){
        q[i].push_back({0,0,Vec{1,-10000000000000}});
    }
    std::sort(g+1,g+m+1,[](const int &a,const int &b){return a>b;});
    for(int i{1};i<=m;i++){
        gsum[i]=gsum[i-1]+g[i];
    }
    for(int i{1};i<=m;i++){
        for(int j{1};j<=p;j++){
            while(q[j-1].size()>1&&cross(q[j-1][1].k,{1,-g[i]})>=0)q[j-1].pop_front();
            dp[i][j]=q[j-1].front().y+q[j-1].front().x*(g[i])+gsum[i]-i*g[i];
            Node cur{i,dp[i][j]-gsum[i],{0,0}};
            while(1){
                cur.k={cur.x-q[j].back().x,cur.y-q[j].back().y};
                if(q[j].size()>1&&cross(q[j].back().k,cur.k)<0)q[j].pop_back();
                else break;
            }
            q[j].push_back(cur);
        }
    }
    int ans{std::numeric_limits<int>::max()};
    for(int i{1};i<=p;i++){
        ans=std::min(ans,dp[m][i]);
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}