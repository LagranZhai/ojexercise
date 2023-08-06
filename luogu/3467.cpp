#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<stack>
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
std::stack<int > s;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int n;
    cin>>n;
    int ans=0;
{
    int w,h;
    for(int i{1};i<=n;i++){
        cin>>w>>h;
        if(s.empty()){
            s.push(h);
            continue;
        }
        while(!s.empty()){
            if(s.top()<h){
                s.push(h);
                break;
            }
            else if(s.top()==h){
                break;
            }
            else if(s.top()>h){
                s.pop();
                ans++;
                if(s.empty()){
                    s.push(h);
                    break;
                }
            }
        }
    }
}
    cout<<ans+s.size()<<"\n";
    cout.flush();
    return 0;
}
