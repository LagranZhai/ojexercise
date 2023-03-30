//luogu1082
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll maxn=2e9;
ll a,b;
ll gcd(ll a,ll b){
    if(!b)return a;
    else return gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1;y=0;
    }
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>a>>b;
    ll x,y;
    exgcd(a,b,x,y);
    while(x<0){
        x+=b/gcd(a,b);
    }
    cout<<x<<endl;
    return 0;
}