#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=2e3;
int n;
std::string a[2];
int dp[maxn+10][maxn+10][2];
int sum[maxn+10];
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    cin>>a[0];
    cin>>a[1];
    bool f1=1;
    for(int i{1};i<a[0].size();i++){
        if(a[0][i]=='0')f1=0;
    }
    for(int i{0};i<a[1].size();i++){
        if(a[1][i]=='0')f1=0;
    }
    if(f1){
        if(n%2==0){
            cout<<n/2<<std::endl;
        }
        else{
            cout<<(n+1)/2<<std::endl;
        }
    }
    else{
        cout<<1<<std::endl;
    }
    return 0;
}