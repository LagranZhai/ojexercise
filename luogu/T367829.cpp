#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
using std::cin,std::ios,std::max,std::min;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
        std::forward<T>(_s)
    ) {}
    Myos<T>& flush() {
        mys<<std::flush;
        return *this;
    }
    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept {
        mys<<std::forward<Traits>(value);
        return *this;
    }
    ~Myos() {
        flush();
    }
};
template<> Myos<std::ostringstream>& Myos<std::ostringstream>::flush() {
        std::cout<<mys.str()<<std::flush;
        mys.str("");
        return *this;
}
//Myos<std::ostream&> cout{std::cout};
Myos<std::ostringstream> cout{std::ostringstream()};
#define int long long
constexpr int maxn=8000;
int a[maxn+10],sum[maxn+10];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int n,m;
    cin>>n>>m;
    for(int i{1};i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    int opt,l,r,x;
    for(int i{1};i<=m;i++){
        cin>>opt;
        if(opt==1){
            cin>>l>>r>>x;
            for(int j{l};j<=r;j++){
                a[j]+=x;
                sum[j]=sum[j-1]+a[j];
            }
        }
        else{
            cin>>l>>r;
            int maxz=0,maxm=0;
            double d=-1e6;
            for(int e{1};e<=r-l+1;e++){
                for(int j{l};j+e-1<=r;j++){
                    if((double)(sum[j+e-1]-sum[j-1])/(double)(e)>d){
                        maxz=sum[j+e-1]-sum[j-1];
                        maxm=e;
                        d=(double)(sum[j+e-1]-sum[j-1])/(double)(e);
                    }
                }
            }
            int g=std::__gcd(maxz,maxm);
            cout<<maxz/g<<" "<<maxm/g<<"\n";
        }
    }
    cout.flush();
    return 0;
}
