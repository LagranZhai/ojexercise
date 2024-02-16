//PC
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=2e5;
double a[maxn],b[maxn];
double sa[maxn],sb[maxn];
int n;
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i]>>b[i];
        a[i]-=1;b[i]-=1;
        a[i]=std::max(0.0,a[i]);
        b[i]=std::max(0.0,b[i]);
    }
    std::sort(a+1,a+n+1,std::greater<>());
    std::sort(b+1,b+n+1,std::greater<>());
    for(int i{1};i<=n;i++){
        sa[i]=a[i]+sa[i-1];
        sb[i]=b[i]+sb[i-1];
    }
    int p{0};
    double ans{0};
    for(int i{0};i<=n;i++){
        while(p<n&&sa[i]-p-1>=sb[p+1]-i)p++;
        if(sa[i]-p>sb[p]-i){
            ans=std::max(ans,std::max(sb[p]-i,(p<n?(sa[i]-p-1):0)));
        }
        else{
            ans=std::max(ans,sb[p]-i);
        }
    }
    cout<<std::fixed<<std::setprecision(4)<<ans<<"\n";
    cout.flush(); 
    return 0;
}