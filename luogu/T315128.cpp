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
constexpr int maxn=12;
int T;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>T;
    long long a;
    while(T--){
        cin>>a;
        int n=__builtin_popcountll(a);
        if(n>=3){
            cout<<"No,Commander\n";
        }
        else{
            if(n==2&&a%2==0){
                cout<<a+(a&(-a))<<"\n";
            }
            else cout<<a+1<<"\n";
        }
    }
    cout.flush();
    return 0;
}
