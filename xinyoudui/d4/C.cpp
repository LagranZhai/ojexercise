//PC
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=(1<<24);
int a[maxn];
using pii=std::pair<int,int>;
pii b[maxn];
void apply(pii &A,pii B){
    pii c{std::numeric_limits<int>::min(),std::numeric_limits<int>::min()};
    if(B.first>A.first)std::swap(A,B);
    c.first=A.first;
    if(A.second>B.first){
        c.second=A.second;
    }
    else{
        c.second=B.first;
    }
    A=c;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    // b[0]={std::numeric_limits<int>::min(),std::numeric_limits<int>::min()};
    int n;
    cin>>n;
    for(int i{0};i<(1<<n);i++){
        cin>>b[i].first;
        b[i].second=std::numeric_limits<int>::min();
    }
    for(int i{0};i<n;i++){
        for(int j{0};j<(1<<n);j++){
            if((j>>i)&1)apply(b[j],b[j^(1<<i)]);
        }
    }
    for(int i{1};i<(1<<n);i++){
        a[i]=b[i].first+b[i].second;
        if(i>1)a[i]=std::max(a[i-1],a[i]);
        cout<<a[i]<<"\n";
    }
    cout.flush();
    return 0;
}