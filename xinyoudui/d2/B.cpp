//PB
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=2e5;
int a[maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    int cnt{0};
    int b{a[n]};
    for(int i{n-1};i>=1;i--){
        if(a[i]<=b){
            b=a[i];
            continue;
        }
        cnt+=(a[i]-1)/b;
        b=a[i]/((a[i]-1)/b+1);
        // cout<<b<<" ";
    }
    cout<<cnt<<"\n";
    cout.flush();
    return 0;
}