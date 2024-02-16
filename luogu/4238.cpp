//P4238
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=4e6,p=998244353,g=3;
int n,m;
int a[maxn],b[maxn],tmp[maxn];
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
    // int l{1<<(lbin(len))};
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
    if(opt==-1){
        int invn{qpow(l,p-2)};
        for(int i{};i<l;i++){
            a[i]=a[i]*invn%p;
        }
    }
}
void polycmp(int *a,int *b,int n){
    std::copy(b,b+n,a);
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    for(int i{};i<n;i++)cin>>a[i];
    b[0]=qpow(a[0],p-2);
    int length=lbin(n),limits{1<<length};
    for(int i{};i<limits;i++){
        r[i]=(r[i>>1]>>1)|((i%2)<<(length-1));
        // cout<<r[i]<<"\n";
    }
    fft(a,limits,1);
    int curn{1};
    while(curn<=n){
        polycmp(tmp,b,curn);
        // fft(b,curn,1);
        for(int i{};i<curn;i++){
            b[i]=b[i]*a[i*(limits/curn)];
        }
        fft(b,curn,-1);
        for(int i{};i<curn;i++){
            b[i]=(p-b[i]);
        }
        b[0]=(b[0]+2)%p;
        fft(b,curn,1);
        for(int i{};i<curn;i++){
            b[i]=b[i]*tmp[i]%p;
        }
        // fft(b,curn,-1);
        curn*=2;
    }
    for(int i{};i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
    cout.flush();
    return 0;
}