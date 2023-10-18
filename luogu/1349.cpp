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
int n,m;
struct Martix{
    int a[3][3]={};
    Martix(int e,int b,int c,int d){
        a[0][0]=e;a[0][1]=b;a[1][0]=c;a[1][1]=d;
    }
    Martix(){a[0][0]=1;a[0][1]=0;a[1][0]=0;a[1][1]=1;}
    void print(){
        cout<<a[0][0]<<" "<<a[0][1]<<"\n"<<a[1][0]<<" "<<a[1][1]<<"\n";
    }
    Martix times(Martix A){
        Martix res{0,0,0,0};
        for(int i{0};i<2;i++){
            for(int j{0};j<2;j++){
                for(int k{0};k<2;k++){
                    res.a[i][j]=(0ll+res.a[i][j]+1ll*a[i][k]*A.a[k][j]%m)%m;
                }
            }
        }
        return res;
    }
};
Martix qpow(Martix a,int b){
    Martix ans{};
    while(b>0){
        if(b&1)ans=ans.times(a);
        b>>=1;
        a=a.times(a);
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int p,q,a1,a2;
    cin>>p>>q>>a1>>a2>>n>>m;
    Martix ans=qpow(Martix{p,q,1,0},n-2);
    // ans.print();
    ans=ans.times(Martix{a2,0,a1,0});
    // ans.print();
    cout<<ans.a[0][0]<<"\n";
    cout.flush();
    return 0;
}
