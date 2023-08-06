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
constexpr int maxn=1e6,p=998244353;
std::vector<int > edg[maxn+10];
int dp[maxn+10],sum[maxn+10];
int id,n,m;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>id>>n>>m;
{
    int u,v;
    for(int i{1};i<=m;i++){
        cin>>u>>v;
        edg[u].push_back(v);
    }
}
    for(int i{1};i<=n;i++){
        dp[i]=(edg[i].size()+1)%p;
        if(!edg[i].empty()){
            for(int v:edg[i]){
                dp[i]+=(0ll+sum[i-1]-sum[v-1]+998244353ll)%p;
                dp[i]%=p;
            }
        }
        sum[i]=(sum[i-1]+dp[i])%p;
    }
    cout<<sum[n]<<"\n";
    cout.flush();
    return 0;
}
