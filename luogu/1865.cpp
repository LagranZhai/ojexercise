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
constexpr int maxm=1e6;
int prime[maxm+100];
std::vector<int > p;
void init(){
    std::fill(prime,prime+maxm+100,1);
    for(int i=2;i<=maxm;i++){
        if(prime[i]){
            p.push_back(i);
        }
        for(auto j:p){
            if(1ll*i*j>maxm)break;
            prime[j*i]=0;
            if(j%i==0){
                break;
            }
        }
        prime[i]+=prime[i-1];
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int n,m;
    cin>>n>>m;
    init();
    int x,y;
    for(int i{1};i<=n;i++){
        cin>>x>>y;
        if(1<=x&&x<=y&&y<=m)cout<<prime[y]-prime[x-1]<<"\n";
        else cout<<"Crossing the line\n";
    }
    cout.flush();
    return 0;
}
