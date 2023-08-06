#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<vector>
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
#define int long long
int breakdown(int N){
    int ans=1;
    for(int i=2;i*i<=N;i++){
        if(N%i==0){
            int j=0;
            while(N%i==0){
                N/=i;
                j++;
            }
            ans*=(j+1);
        }
    }
    if(N!=1){  
        ans*=2;
    }
    return ans;
}
int n;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    cout<<breakdown(n-1)<<"\n";
    cout.flush();
    return 0;
}
