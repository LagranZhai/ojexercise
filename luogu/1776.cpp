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
constexpr int maxn=100,maxW=4e4;
std::deque<int > q;
int v[maxn*2],w[maxn*2],m[maxn*2];
int dp[maxn*2][maxW+100];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int n,W;
    cin>>n>>W;
    for(int i{1};i<=n;i++){
        cin>>v[i]>>w[i]>>m[i];
    }
    for(int i{1};i<=n;i++){
        for(int j{0};j<w[i];j++){
            q.clear();
            for(int k{0};k*w[i]+j<=W;k++){
                while(!q.empty()&&k-q.front()>m[i])q.pop_front();
                while(!q.empty()&&dp[i-1][q.back()*w[i]+j]-q.back()*v[i]<dp[i-1][k*w[i]+j]-k*v[i])q.pop_back();
                q.push_back(k);
                dp[i][k*w[i]+j]=max(dp[i][k*w[i]+j],dp[i-1][q.front()*w[i]+j]-q.front()*v[i]+k*v[i]);
            }
        }
    }
    int ans=0;
    for(int i{0};i<=W;i++){
        ans=max(ans,dp[n][i]);
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
