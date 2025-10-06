#include<bits/stdc++.h>
using std::cin,std::cout;
using ll= long long;
constexpr ll p{(int)1e9+7},maxn{(int)4e6+10};
int n,m;
ll qpow(int a,int x){
    ll res{a},ans{1};
    while(x){
        if(x&1)ans=ans*res%p;
        res=res*res%p;
        x>>=1;
    }
    return ans;
}
ll fac[maxn],inv[maxn];
void init(){
    fac[0]=1;
    for(int i{1};i<maxn;i++){
        fac[i]=fac[i-1]*i%p;
    }
    inv[maxn-1]=qpow(fac[maxn-1],p-2);
    for(int i{maxn-2};i>=1;i--){
        inv[i]=inv[i+1]*(i+1)%p;
    }
    inv[0]=1;
}
ll C(int a,int b){
    return (fac[a]*inv[b]%p)*inv[a-b]%p;
}
ll count(int x,int y,int now,int nxt,bool mi){
    int o{x};
    x=y-now;y=o+now;
    if(x<0||y<0){
        return 0;
    }
    return (count(x,y,2*now-nxt,now,!mi)+(mi?-1:1)*C(x+y,x))%p;
}
// int dp[200][200];

int main(){
    std::ios::sync_with_stdio(false);
    cin>>n>>m;
    init();
    ll ans{((C(m+2*n+1,n)+count(m+n+1,n,1,-m-2,1))%p+count(m+n+1,n,-m-2,1,1))%p};
    // dp[0][0]=1;
    // for(int i{0};i<=n;i++){
    //     for(int j{i};j<i+m+2;j++){
    //         if(i==0&&j==0){
    //             dp[i][j]=1;
    //             continue;
    //         }
    //         if(i==0)dp[i][j]=dp[i][j-1];
    //         else dp[i][j]=dp[i][j-1]+dp[i-1][j];
    //     }
    // }
    cout<<(ans+p)%p<<std::endl;
    return 0;
}