//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
int getw(int x){
    int c{0};
    while(x){
        x/=10ll;
        c++;
    }
    return c;
}
int getd(int n){
    int ans{getw(n)};
    for(int i{2};i<=std::sqrt(n);i++){
        if(n%i==0){
            ans=std::min(ans,std::max(getw(i),getw(n/i)));
        }
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;
    cout<<getd(n)<<"\n";
    cout.flush();
    return 0;
}