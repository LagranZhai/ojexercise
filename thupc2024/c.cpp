#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
//constexpr int maxn=
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,l,r;
    double p;
    cin>>n>>p>>l>>r;
    cout<<std::fixed<<std::setprecision(6)<<(double)(r-l+1)*p<<"\n";
    cout.flush();
    return 0;
}