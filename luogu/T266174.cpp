#include<iostream>
using namespace std;
using ll=long long;
ll solve(ll x){
    ll low=x%3ll;x/=3ll;
    if(low==2){
        return 0;
    }
    ll res=1;
    while(x>0){
        low=x%3ll;
        x/=3;
        if(low==1)res*=2;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    ll x;
    while(t--){
        cin>>x;
        cout<<solve(x)<<endl;
    }
    cout.flush();
    return 0;
}
