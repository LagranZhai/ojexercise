#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=3000;
int n,k;
int a[maxn*2];
int sum[maxn*2];
int b[maxn*2],c[maxn*2];
int premax[maxn*2],sufmax[maxn*2];
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    for(int i{1};i<=n;i++){
        sum[i]=sum[i-1]^a[i];
    }
    int maxx=0;
    for(int r{1};r<=n;r++){
        for(int l{1};l<=r;l++){
            maxx=std::max(maxx,sum[r]^sum[l-1]);
            b[r]=std::max(b[r],sum[r]^sum[l-1]);
            c[l]=std::max(c[l],sum[r]^sum[l-1]);
        }
    }
    for(int i{1};i<=n;i++){
        premax[i]=std::max(premax[i-1],b[i]);
    }
    for(int i{n};i>=1;i--){
        sufmax[i]=std::max(sufmax[i+1],c[i]);
    }
    int max2=0;
    for(int i{1};i<n;i++){
        max2=std::max(max2,premax[i]+sufmax[i+1]);
    }
    if(k==1){
        cout<<maxx<<std::endl;
    }
    else{
        if(k==2){
            cout<<max2<<std::endl;
        }
        else{
            cout<<maxx<<std::endl;
        }
    }
    return 0;
}