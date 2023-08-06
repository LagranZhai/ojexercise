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
constexpr int maxn=200;
int n,m,k;
int p1[maxn+100][maxn+100],p2[maxn+100][maxn+100],p3[maxn+100][maxn+100];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m>>k;
    int a;
    for(int i{1};i<=k;i++){
        for(int j{1};j<=n;j++){
            for(int l{1};l<=m;l++){
                cin>>a;
                if(a==1){
                    p1[i][j]=1;
                    p2[i][l]=1;
                    p3[l][j]=1;
                }
            }
        }
    }
    for(int i{k};i>=1;i--){
        for(int j{1};j<=n;j++){
            cout<<p1[i][j]<<" ";
        }
        cout<<"\n";
    }
    for(int i{k};i>=1;i--){
        for(int j{m};j>=1;j--){
            cout<<p2[i][j]<<" ";
        }
        cout<<"\n";
    }
    for(int i{m};i>=1;i--){
        for(int j{1};j<=n;j++){
            cout<<p3[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout.flush();
    return 0;
}
