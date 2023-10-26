#include<bits/stdc++.h>
using std::cin;using std::cout;using std::ios;
#define int long long
constexpr int p=1e9+7;
int qpow(int a,int b){
    int c{1};
    while(b>0){
        if(b&1)c=c*a%p;
        a=a*a%p;
        b>>=1;
    }
    return c;
}
signed main(){
    freopen("magic.in","r",stdin);
    freopen("magic.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;
    cin>>n;
    int ans=(qpow(3,n+1)-1+p)%p;
    ans=ans*qpow(2,p-2)%p;
    cout<<ans<<std::endl;
    return 0;
}
