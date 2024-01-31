#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=2e6,maxm=2e6;
#define int long long
int x,y,m,n,l;
void exgcd(int &x,int &y,int a,int b){
    if(!b){
        x=1;y=0;
        return ;
    }
    else{
        exgcd(y,x,b,a%b);y-=a/b*x;return ;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>x>>y>>m>>n>>l;
    int d{std::__gcd(l,m-n)};
    if((y-x)%d!=0){
        cout<<"Impossible\n";
    }
    else{
        int x{},y{};
        exgcd(x,y,l,m-n);
        y*=(y-x)/d;
        if()
        cout<<y<<"\n";
    }
    cout.flush();
    return 0;
}