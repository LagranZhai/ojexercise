#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=1e7;
int p[maxn+100],vis[maxn+100],cnt=0;
vector<int > minp[maxn+100];
void euler(){
    for(int i=2;i<=maxn;i++){
        if(!vis[i]){
            p[++cnt]=i;
            minp[i].push_back(i);
        }
        for(int j=1;j<=cnt;j++){
            if(1ll*p[j]*i>maxn)break;
            vis[p[j]*i]=1;
            minp[p[j]].push_back(p[j]*i);
            if(i%p[j]==0){
                break;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    euler();
    ll n,p;
    cin>>n>>p;
    // for(int i=0;i<100;i++){
    //     cout<<minp[p][i]<<' ';
    // }
    if(p<=maxn){
        if(n<=minp[p].size()){
            cout<<minp[p][n-1]<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }
    else{
        if(n==1){
            if(p<=1e9){
                cout<<p<<endl;
            }
        }
        if(n==2){
            if(p*p<=1e9){
                cout<<p*p<<endl;
            }
        }
        else cout<<0<<endl;
    }
    return 0;
}