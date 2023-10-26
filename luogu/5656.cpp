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
#define int long long
int exgcd(int a,int &x,int b,int &y){
    if(!b){
        x=1;y=0;
        return a;
    }
    int d=exgcd(b,x,a%b,y);
    int lx=x;
    x=y;y=lx-(a/b)*y;
    return d;
}
void solve(int a,int b,int c){
    int d=std::__gcd(a,b);
    if(c%d!=0){
        cout<<"-1\n";
        return ;
    }
    int g=c/d,x=0,y=0;
    exgcd(a,x,b,y);
    x*=g;y*=g;
    // cout<<x<<" "<<y;
    int mi,ma;
    if(x<0){
        mi=(-x)/(b/d)+1;
    }
    else{
        if(x%(b/d)==0)mi=(-x)/(b/d)+1;
        else mi=(-x)/(b/d);
    }
    if(y<0){
        ma=y/(a/d)-1;
    }
    else{
        if(y%(a/d)==0)ma=y/(a/d)-1;
        else ma=y/(a/d);
    }
    if(mi<=ma){
        cout<<ma-mi+1<<" "<<x+(b/d)*mi<<" "<<y-(a/d)*ma<<" "<<x+(b/d)*ma<<" "<<y-(a/d)*mi<<"\n";
    }
    else{
        cout<<x+(b/d)*mi<<" "<<y-(a/d)*ma<<"\n";
    }
    return ;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int n;
    cin>>n;
    int a,b,c;
    for(int i{1};i<=n;i++){
        cin>>a>>b>>c;
        solve(a,b,c);
    }
    cout.flush();
    return 0;
}
