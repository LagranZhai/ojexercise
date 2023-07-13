#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<deque>
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
constexpr int maxn=2000;
int T,maxP,W,ap[maxn*2],as[maxn*2],bp[maxn*2],bs[maxn*2],dp[maxn+100][maxn+100];
std::deque<int > q;
int main() {
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>T>>maxP>>W;
    for(int i{1};i<=T;i++){
        cin>>ap[i]>>bp[i]>>as[i]>>bs[i];
    }
    for(int i{1};i<=T;i++){
        for(int j{0};j<=as[i];j++){
            dp[i][j]=-ap[i]*j;
        }
        for(int j{0};i<=maxP;j++){
            dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
        if(i-W<1)continue;
        q.clear();
        for(int j{0};j<=maxP;j++){
            while(!q.empty()&&j-q.front()>as[i])q.pop_front();
            while(!q.empty()&&dp[i-W-1][q.back()]+q.back()*ap[i]<dp[i-W-1][j]+j*ap[i])q.pop_back();
            q.push_back(j);
            if(!q.empty())dp[i][j]=max(dp[i][j],dp[i-W-1][q.front()]+q.front()*ap[i]-j*ap[i]);
        }
        q.clear();
        for(int j{maxP};j>=0;j--){
            while(!q.empty()&&q.front()-j>bs[i])q.pop_front();
            while(!q.empty()&&dp[i-W-1][q.back()]+q.back()*bp[i]<dp[i-W-1][j]+j*bp[i])q.pop_back();
            q.push_back(j);
            if(!q.empty())dp[i][j]=max(dp[i][j],dp[i-W-1][q.front()]+q.front()*bp[i]-j*bp[i]);
        }
    }
    cout<<dp[T][0]<<"\n";
    cout.flush();
    return 0;
}
