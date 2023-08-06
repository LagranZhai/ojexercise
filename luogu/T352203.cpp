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
constexpr int maxn=5e5;
long long a[maxn*2],b[maxn*2],n;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i]>>b[i];
    }
    long long e=0,maxr=0;
    for(int i{1};i<=n-1;i++){
        maxr=max(maxr,a[i]+b[i]);
        e=max(e,a[i+1]-maxr);
    }
    cout<<e<<"\n";
    cout.flush();
    return 0;
}
