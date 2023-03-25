#include<bits/stdc++.h>
#define int long long
using namespace std;
int gcd(int a,int b){
    if(b==0)return a;
    else return gcd(b,a%b);
}
signed main(){
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    int a;
    cin>>a;
    int b;
    for(int i=2;i<=n;i++){
        cin>>b;
        b=abs(b);
        a=gcd(a,b);
    }
    cout<<a<<endl;
    return 0;
}