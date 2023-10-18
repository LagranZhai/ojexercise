#include<iostream>
#include<algorithm>
#include<iomanip>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e6;
double dp1[maxn+100],dp2[maxn+100],dp3[maxn+100],p[maxn+100];
int n;
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>p[i];
    }
    for(int i{1};i<=n;i++){
        dp1[i]=(dp1[i-1]+1.0)*p[i];
        dp2[i]=(dp2[i-1]+2.0*dp1[i-1]+1.0)*p[i];
        dp3[i]=dp3[i-1]+(3.0*dp2[i-1]+3.0*dp1[i-1]+1.0)*p[i];
    }
    cout<<std::fixed<<std::setprecision(1);
    cout<<dp3[n]<<"\n";
    return 0;
}