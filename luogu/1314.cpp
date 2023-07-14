#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<ranges>
#include<limits>
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
constexpr int maxn=2e5;
long long w[maxn+100],v[maxn+100],sum[maxn+100],cnt[maxn+100];
int l[maxn+100],r[maxn+100];
int n,m;
long long s;
long long solve(int w_){
    std::fill(sum,sum+maxn+100,0);
    std::fill(cnt,cnt+maxn+100,0);
    for(int i{1};i<=n;i++){
        cnt[i]=cnt[i-1]+(w[i]>=w_);
        sum[i]=sum[i-1]+(w[i]>=w_)*v[i];
    }
    long long y=0;
    for(int i{1};i<=m;i++){
        y+=(cnt[r[i]]-cnt[l[i]-1])*(sum[r[i]]-sum[l[i]-1]);
    }
    return y;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m>>s;
    int maxw=0;
{
    int w_,v_;
    for(int i{1};i<=n;i++) {
        cin>>w_>>v_;
        maxw=max(maxw,w_);
        w[i]=w_;
        v[i]=v_;
    }
}
    for(int i{1};i<=m;i++){
        cin>>l[i]>>r[i];
    }
    long long ans=std::numeric_limits<long long>::max();
{
    int l=0,r=maxw,mid=(l+r)/2;
    long long delta=0;
    while(l<r){
        mid=(l+r)/2;
        delta=solve(mid)-s;
        if(delta>0){
            l=mid+1;
        }
        else r=mid;
        ans=min(std::abs(delta),ans);
    }
    mid=(l+r)/2;
    delta=solve(mid)-s;
    ans=min(std::abs(delta),ans);
}
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
