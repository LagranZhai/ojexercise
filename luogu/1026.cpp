#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
using std::cin,std::ios,std::max,std::min;
template<class T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
            std::forward<T>(_s)
            ){}
    ~Myos()noexcept{
        std::cout<<std::flush;
    };
};
template<>
Myos<std::ostringstream>::~Myos()noexcept{
    std::cout<<mys.str()<<std::flush;
}
auto&& cout = Myos<std::ostringstream>(std::ostringstream()).mys;
//auto&& cout = Myos<std::ostream&>(std::cout).mys;
constexpr int maxn=200,maxk=40,maxs=6;
int dp[maxn*2][maxk],w[maxn*2][maxn*2];
std::string dic[maxs*2];
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int p,k;
    cin>>p>>k;
    std::string t,s;
    while(p--){
        cin>>t;
        s+=t;
    }
    int n;cin>>n;
    for(int i{1};i<=n;i++){
        cin>>dic[i];
    }
    for(int i{s.size()-1};i>=0;i--){
        for(int j{i};j>=0;j--){
            if([&](int x,int y)->bool{
                for(int i{1};i<=n;i++){
                    for(int j=0;j<dic[i].size()&&j+x<=y;j++){
                        if(s[x+j]==dic[i][j]){
                            if(j==dic[i].size()-1)return 1;
                        }
                        else break;
                    }
                }
                return 0;
            }(i,j)){
                w[i][j]=w[i+1][j]+1;
            }
            else w[i][j]=w[i+1][j];
        }
    }
    for(int i{0};i<s.size();i++){
        dp[0][i]=w[0][i];
        cout<<dp[0][i]<<" ";
    }
    for(int i{1};i<=k;i++){
        for(int j{0};j<s.size();j++){
            for(int k{i-1};k<j;k++){
                dp[i][j]=max(dp[i][j],dp[i-1][k]+w[k+1][j]);
            }
        }
    }
    cout<<dp[k][s.size()-1];
    return 0;
}
