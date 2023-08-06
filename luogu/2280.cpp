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
constexpr int maxn=5e3;
int n,m;
int a[maxn+10][maxn+10];
int solve(int x,int y,int (*sum)[maxn+10]) {
    for(int i{1};i<=x;i++){
        for(int j{1};j<=y;j++){
            sum[i][j]+=sum[i][j-1];
        }
    }
    for(int i{1};i<=x;i++){
        for(int j{1};j<=y;j++){
            sum[i][j]+=sum[i-1][j];
        }
    }
    int ans=0;
    for(int i{min(m,x)};i<=x;i++){
        for(int j{min(m,y)};j<=y;j++){
            ans=max(ans,sum[i][j]-sum[max(0,i-m)][j]-sum[i][max(0,j-m)]+sum[max(0,i-m)][max(0,j-m)]);
        }
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
    int maxx=0,maxy=0;
{
    int x,y,z;
    for(int i{1};i<=n;i++){
        cin>>x>>y>>z;
        maxx=max(maxx,x+1);
        maxy=max(maxy,y+1);
        a[x+1][y+1]=z;
    }
}
    cout<<solve(maxx,maxy,a)<<"\n";
    cout.flush();
    return 0;
}
