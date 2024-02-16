//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=1e6;
int n;
int a[maxn],s[maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    int sum{0};
    for(int i{1};i<=n;i++){
        cin>>a[i];
        sum+=a[i];
    }
    int v{sum/n};
    for(int i{1};i<=n;i++){
        s[i]=s[i-1]+a[i]-v;
    }
    std::sort(s+1,s+n+1);
    int ans{0};
    for(int i{1};i<=n;i++){
        ans+=std::abs(s[(n+1)/2]-s[i]);
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}