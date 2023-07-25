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
constexpr int maxn=5e3,p=1e8;
std::string s,t;
int dp[2][maxn+10],num[2][maxn+10];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>s>>t;
    for(int i{0};i<t.size();i++){
        num[0][i]=1;
    }
    num[1][0]=1;
    for(int i{1};i<s.size();i++){
        for(int j{1};j<t.size();j++){
            num[i%2][j]=0;
            if(s[i-1]==t[j-1]){
                dp[i%2][j]=dp[(i+1)%2][j-1]+1;
                num[i%2][j]+=num[(i+1)%2][j-1];num[i%2][j]%=p;
            }
            else{
                dp[i%2][j]=max(dp[(i+1)%2][j],dp[i%2][j-1]);
            }
            if(dp[i%2][j]==dp[(i+1)%2][j]){
                num[i%2][j]+=num[(i+1)%2][j];num[i%2][j]%=p;
            }
            if(dp[i%2][j]==dp[i%2][j-1]){
                num[i%2][j]+=num[i%2][j-1];num[i%2][j]%=p;
                if(s[i-1]!=t[j-1]&&dp[i%2][j]==dp[(i+1)%2][j-1]){
                    num[i%2][j]=num[i%2][j]+(p-num[(i+1)%2][j-1])%p;num[i%2][j]%=p;
                }
            }
        }
    }
    cout<<dp[(s.size()-1)%2][t.size()-1]<<"\n"<<num[(s.size()-1)%2][t.size()-1]<<"\n";
    cout.flush();
    return 0;
}
