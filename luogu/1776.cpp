#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<queue>
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
constexpr int maxn=100;
std::deque<int > q;
int v[maxn*2],w[maxn*2],m[maxn*2];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int n,W;
    cin>>n>>W;
    for(int i{1};i<=n;i++){
        cin>>v[i]>>w[i]>>m[i];
    }
    for(int i{1};i<=n;i++){
        q.clear();
        q.push()
        for(int j{W};j>=0;j--){
            while(q.front())
        }
    }
    cout.flush();
    return 0;
}
