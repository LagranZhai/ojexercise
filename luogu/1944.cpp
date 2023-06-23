#include<iostream>
#include<sstream>
#include<algorithm>
using std::cin,std::ios;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& s)noexcept:mys(std::forward<T>(s)) {}
    ~Myos()noexcept {
        mys<<std::flush;
    }
};
template<> 
Myos<std::ostringstream>::~Myos()noexcept {
    std::cout<<mys.str()<<std::flush;
};
Myos<std::ostringstream> myos{std::ostringstream()};
//Myos<std::ostream&> myos{std::cout};
auto&& cout=myos.mys;
constexpr int maxn=1e6;
int dp[maxn+10];
int main(){
    ios::sync_with_stdio(false);
    std::string s;
    cin>>s;
    int ansx=0;
    for(int i{1};i<s.size();i++){
        if((s[i-1-dp[i-1]]=='('&&s[i]==')')
         ||(s[i-1-dp[i-1]]=='['&&s[i]==']')){
            dp[i]=dp[i-1]+2+dp[i-1-dp[i-1]-1];
            if(dp[i]>dp[ansx])ansx=i;
        }   
    }
    for(int i=ansx-dp[ansx]+1;i<=ansx;i++)cout<<s[i];
    return 0;
}
