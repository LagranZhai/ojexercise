#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=50,maxw=50;
#define int long long
int a[maxn*2];
int d[maxn*2];
int n;
void insert(int x){
    for(int i{maxw};i>=0;i--){
        if(x&(1ll<<i)){
            if(d[i]){
                x^=d[i];
            }
            else{
                d[i]=x;
                break;
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
        insert(a[i]);
    }
    int ans{0};
    for(int i{maxw};i>=0;i--){
        if((ans^d[i])>ans){
            ans=ans^d[i];
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}