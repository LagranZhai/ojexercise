#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=4e5;
#define int long long
int a[maxn];
int h[maxn];
int n;
std::vector<int > hei;
int gethei(int x){
    return std::lower_bound(std::begin(hei),std::end(hei),x)-std::begin(hei)+1;
}
int lowbit(int x){
    return x&(-x);
}
void update(int x){
    while(x<=n){
        // std::cerr<<1;
        a[x]+=1;
        x+=lowbit(x);
    }
    return ;
}
int query(int x){
    int ans=0;
    while(x>0){
        // std::cerr<<2;
        ans+=a[x];
        x-=lowbit(x);
    }
    return ans;
}
int solve(){
    std::fill(a,a+maxn,0);
    int ans=0;
    for(int i{n};i>=1;i--){
        ans+=query(gethei(h[i]));
        update(gethei(h[i]));
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>h[i];
        hei.push_back(h[i]);
    }
    std::sort(std::begin(hei),std::end(hei));
    int ans=solve();
    for(int i{1};i<=n;i++){
        for(int j{i+1};j<=n;j++){
            std::swap(h[i],h[j]);
            ans=std::min(ans,solve()+1);
            std::swap(h[i],h[j]);
        }
    }
    cout<<ans<<std::endl;
    return 0;
}