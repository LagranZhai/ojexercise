//P2158
//phi
#include<iostream>
#include<algorithm>
using std::cin,std::cout,std::ios;
constexpr int maxn=4e4;
int phi[maxn+100],p[maxn+100],cnt=0;
bool isp[maxn+100];
void getphi(){
    std::fill(isp,isp+maxn+100,1);
    isp[1]=0;
    phi[1]=0;
    for(int i{2};i<=maxn;i++){
        if(isp[i]){
            p[++cnt]=i;
            phi[i]=i-1;
        }
        for(int j{1};j<=cnt;j++){
            if(p[j]*i>maxn)break;
            isp[p[j]*i]=0;
            if(i%p[j]==0){
                phi[i*p[j]]=p[j]*phi[i];
                break;
            }
            else{
                phi[i*p[j]]=phi[p[j]]*phi[i];
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    getphi();
    int n;
    cin>>n;
    int ans=0;
    for(int i{1};i<n;i++){
        // cout<<phi[i]<<"\n";
        ans+=phi[i];
    }
    if(n==1)cout<<0<<"\n";
    else cout<<(ans)*2+3<<"\n";
    return 0;
}