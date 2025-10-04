#include<bits/stdc++.h>
using std::cin,std::cout;
using ll=long long;
constexpr int maxn=1e6+10;
ll a[maxn]{},n,h,low[maxn];
int main(){
    std::ios::sync_with_stdio(false);
    cin>>n>>h;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    std::priority_queue<ll> q1;
    std::priority_queue<ll,std::vector<ll>,std::greater<ll>> q2;    
    ll ans{},l{};
    for(int i{1};i<=n;i++){
        if(i==1){
            q1.push(a[i]);q2.push(a[i]);
            continue;
        }
        l+=h;
        ll m1{q1.top()-l},m2{q2.top()+l};
        if(a[i]>=m1&&a[i]<=m2){
            q1.push(a[i]+l);q2.push(a[i]-l);
        }
        else if(a[i]<m1){
            q1.pop();q2.push(m1-l);
            q1.push(a[i]+l);q1.push(a[i]+l);
            ans+=m1-a[i];
        }
        else if(a[i]>m2){
            q2.pop();q1.push(m2+l);
            q2.push(a[i]-l);q2.push(a[i]-l);
            ans+=a[i]-m2;
        }
    }
    cout<<ans<<std::endl;
    cout.flush();
    return 0;
}
