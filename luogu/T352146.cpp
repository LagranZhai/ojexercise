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
constexpr int maxn=5e5,maxk=1e4;
long long num[maxn*3],p[maxk*4]={};
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    long long a,n,k;
    cin>>n>>k;
    long long sum=0;
    for(long long i{1};i<=2*n;i++){
        cin>>num[i];
        p[i%k]+=num[i];
    }
    for(long long i{1};i<=2*n;i++){
        if(i%2ll==0){
            cout<<num[i]<<" ";
        }
        else cout<<p[i%k]%i<<" ";
    }
    cout<<"\n";
    cout.flush();
    return 0;
}
