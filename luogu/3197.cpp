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
constexpr int p=100003;
int qpow(int a,int b){
    int c=1;
    while(b>0){
        if(b&1)c=(c*a)%p;
        b>>=1;
        a=(a*a)%p;
    }
    return c;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int n,m;
    cin>>m>>n;
    cout<<(qpow(m,n)-m*qpow(m-1,n-1)%p+p)%p<<"\n";
    cout.flush();
    return 0;
}
