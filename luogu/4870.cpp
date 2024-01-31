#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=300;
std::vector<int > x;
int dp[maxn*2][maxn*2][2];
int n,m;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int t;
    for(int i{1};i<=n;i++){
        cin>>t;
        x.push_back(t);
    }
    std::sort(std::begin(x),std::end(x));
    auto pos1=std::lower_bound(std::begin(x),std::end(x),0);
    if(pos1!=x.end()){
        pos1
    }
    for(int num{1};num<=n;num++){
        std::fill(dp[0][0],dp[0][0]+(maxn*2)*(maxn*2)*2,0);
        int lb=std::lower_bound(x,)
        for(int l{1};l<=num;l++){
            for(int i{1};i+l-1<=n;i++){

            }
        }
    }
    return 0;
}