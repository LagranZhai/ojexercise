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
constexpr int maxn=2e5,maxk=50;
int a[maxn*2],b[maxn*2],n,k,p;
int cnt[maxk*2],sum[maxk*2][maxn*2];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>k>>p;
    for(int i{1};i<=n;i++){
        cin>>a[i]>>b[i];
    }
    for(int i{1};i<=n;i++){
        for(int j{0};j<k;j++){
            sum[j][i]=sum[j][i-1];
        }
        sum[a[i]][i]+=1;
    }
    long long ans=0;
    for(int i{n};i>=1;i--){
        cnt[a[i]]++;
        if(b[i]<=p){
            ans+=cnt[a[i]]-1;
            for(int j{0};j<k;j++){
                ans+=1ll*cnt[j]*sum[j][i-1];
                cnt[j]=0;
            }
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
