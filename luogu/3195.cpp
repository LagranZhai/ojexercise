#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=5e4;
#define int long long
int n,l;
int c[maxn*2],sum[maxn*2];
struct Node{
    int x,y;
    double k;
};
constexpr double eps=1e-14;
int dp[maxn*2];
double getk(Node x,Node y){
    return (double)(y.y-x.y)/(double)(y.x-x.x);
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>l;
    for(int i{1};i<=n;i++)cin>>c[i];
    for(int i{1};i<=n;i++){
        sum[i]=sum[i-1]+c[i];
    }
    for(int i{1};i<=n;i++){
        sum[i]+=i;
    }
    std::deque<Node> q;
    q.push_back({0,(l+1)*(l+1),(double)std::numeric_limits<double>::lowest()});
    for(int i{1};i<=n;i++){
        while(q.size()>1&&(double)sum[i]-q[1].k>eps)q.pop_front();
        dp[i]=q.front().y-q.front().x*sum[i]+sum[i]*sum[i]-2*(l+1)*sum[i];
        Node cur{2*sum[i],dp[i]+(sum[i]+l+1)*(sum[i]+l+1),0};
        while(!q.empty()){
            cur.k=getk(q.back(),cur);
            if(q.back().k-cur.k>eps)q.pop_back();
            else break;
        }
        q.push_back(cur);
    }
    cout<<dp[n]<<"\n";
    cout.flush();
    return 0;
}