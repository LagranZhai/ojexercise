#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int maxn=3e5;
int n,s;
int csum[maxn*2],fsum[maxn*2];
struct Vec{
    int dx,dy;
};
int cross(Vec a,Vec b){
    return a.dx*b.dy-b.dx*a.dy;
}
struct Node{
    int x,y;
    Vec k;
    // bool operator>(const Node A)const;
    // bool operator<(const Node A)const;
};
// bool Node::operator>(const Node A)const{
//     return cross(k,A.k)<0;
// }
// bool Node::operator<(const Node A)const{
//     return cross(k,A.k)>=0;
// }
int dp[maxn*2];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>s;
    for(int i{1};i<=n;i++){
        cin>>csum[i]>>fsum[i];
    }
    for(int i{1};i<=n;i++){
        csum[i]+=csum[i-1];
        fsum[i]+=fsum[i-1];
    }
    std::deque<Node> q;
    q.push_back({0,0,{1,-100000}});
    for(int i{1};i<=n;i++){
        auto it=(std::lower_bound(q.begin(),q.end(),Node{0,0,{1,csum[i]}},[](const Node &A,const Node &B){return cross(A.k,B.k)>=0;}));
        it--;
        dp[i]=it->y-it->x*csum[i]+s*fsum[n]+fsum[i]*csum[i];
        Node cur{fsum[i],dp[i]-s*fsum[i],{0,0}};
        while(1){
            cur.k={cur.x-q.back().x,cur.y-q.back().y};
            if(q.size()>1&&cross(q.back().k,cur.k)<=0)q.pop_back();
            else break;
        }
        q.push_back(cur);
    }
    // for(int i{1};i<=n-1;i++)cout<<dp[i]<<"\n";
    cout<<dp[n]<<"\n";
    cout.flush();
    return 0;
}