//P3803
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=4e6;
const double pi=std::acos(-1);
constexpr std::complex<double> w0{1,0};
int n,m;
std::complex<double> a[maxn],b[maxn];
int r[maxn];
int lbin(int x){
    int c{0},b{1};
    while(b<=x){
        c++;b<<=1;
    }
    return c;
}
void fft(std::complex<double> *a,int l,int opt){
    for(int i{};i<l;i++){
        if(i<r[i])std::swap(a[i],a[r[i]]);
    }
    for(int d{2};d<=l;d<<=1){
        int h{d/2};
        std::complex<double> w1{std::cos(pi/(double)h),opt*std::sin(pi/(double)h)};
        for(int i{};i<l;i+=d){
            std::complex<double> w{w0};
            for(int j{i};j<i+h;j++){
                std::complex<double> t{a[j+h]*w},o{a[j]};
                a[j]=o+t;
                a[j+h]=o-t;
                w*=w1;
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
        a[i]=a[i]*b[i];
    }
    fft(a,limit,-1);
    // std::reverse(a+1,a+limit);
    for(int i{};i<=n+m;i++){
        cout<<(int)(a[i].real()/limit+0.5)<<" ";
    }
    cout<<"\n";
    cout.flush();
    return 0;
}