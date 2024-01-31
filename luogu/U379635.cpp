#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=100;
int asum[maxn*2],acnt[maxn*2],bsum[maxn*2],bcnt[maxn*2];
int ans[maxn*2];
int n;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    int x,y;
    // std::vector<int> up;
    int res{0};
    for(int i{1};i<=n;i++){
        cin>>x>>y;
        bcnt[y]++;acnt[x]++;
        int cur{0};
        for(int j{y};j<=maxn;j++){
            bsum[j]++;
        }
        for(int j{x};j>=1;j--){
            asum[j]++;
            if(bsum[ans[j]]>=asum[j]&&asum[j]>bsum[ans[j]-1]){
                if(acnt[j]>0)cur=std::max(cur,j+ans[j]);
                continue;
            }
            if(acnt[j]==0)continue;
            ans[j]=std::lower_bound(bsum+1,bsum+maxn+1,asum[j])-std::begin(bsum);
            // cout<<ans[j]<<" ";
            cur=std::max(cur,j+ans[j]);
        }
        for(int j{1};j<=maxn;j++){
            if(bsum[ans[j]]>=asum[j]&&asum[j]>bsum[ans[j]-1]){
                if(acnt[j]>0)cur=std::max(cur,j+ans[j]);
                continue;
            }
            if(acnt[j]==0)continue;
            ans[j]=std::lower_bound(bsum+1,bsum+maxn+1,asum[j])-std::begin(bsum);
            cur=std::max(cur,j+ans[j]);
        }
        cout<<cur<<"\n";
    }
    cout.flush();
    return 0;
}