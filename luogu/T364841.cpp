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
constexpr int maxn=3e5;
#define int long long
int n,m;
int a[maxn+100];
bool solve(int b){
    int s=0;
    for(int i{1};i<=m;i++){
        if(a[i]%b==0){
            s+=a[i]/b;
        }
        else{
            s+=a[i]/b+1ll;
        }
    }
    if(s>n)return false;
    else return true;
}
signed main(){
    freopen("")
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
    for(int i{1};i<=m;i++){
        cin>>a[i];
    }
    int l=1,r=n,mid=(l+r)/2;
    while(l<r){
        mid=(l+r)/2;
        if(solve(mid)){
            r=mid;
        }
        else{
            l=mid+1;
        }
    }
    cout<<l<<"\n";
    cout.flush();
    return 0;
}
