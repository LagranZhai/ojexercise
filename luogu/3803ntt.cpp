//P3803ntt
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=4e6,p=998244353,g=3;
int n,m;
int a[maxn],b[maxn];
int r[maxn];
int qpow(int a,int b){
    int c{1};
    while(b){
        if(b&1)c=c*a%p;
        a=a*a%p;
        b>>=1;
    }
    return c;
}
const int invg{qpow(g,p-2)};
int lbin(int x){
    int c{0},b{1};
    while(b<=x){
        c++;b<<=1;
    }
    return c;
}
void fft(int *a,int l,int opt){
    for(int i{};i<l;i++){
        if(i<r[i])std::swap(a[i],a[r[i]]);
    }
    for(int d{2};d<=l;d<<=1){
        int h{d/2};
        int w1{qpow(((opt==1)?g:invg),(p-1)/d)};
        for(int i{};i<l;i+=d){
            int w{1};
            for(int j{i};j<i+h;j++){
                int t{a[j+h]*w%p},o{a[j]%p};
                a[j]=(o+t)%p;
                a[j+h]=(o-t+p)%p;
                w=w*w1%p;
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    for(int i{};i<=n;i++)cin>>a[i];
    for(int i{};i<=m;i++)cin>>b[i];
    int length{lbin(n+m)};
    for(int i{};i<(1<<length);i++){
        r[i]=(r[i>>1]>>1)|((i%2)<<(length-1));
        // cout<<r[i]<<"\n";
    }
    int limit{(1<<length)};
    fft(a,limit,1);
    fft(b,limit,1);
    for(int i{};i<limit;i++){
        a[i]=a[i]*b[i]%p;
    }
    fft(a,limit,-1);
    // std::reverse(a+1,a+limit);
    int invn{qpow(limit,p-2)};
    for(int i{};i<=n+m;i++){
        cout<<a[i]*invn%p<<" ";
    }
    cout<<"\n";
    cout.flush();
    return 0;
}