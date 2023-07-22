#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<stack>
using std::cin,std::ios,std::max,std::min,std::size_t;
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
constexpr int maxn=700,p=1000000007;
std::string s;
size_t match[maxn*2];
std::stack<int > st;
int dp[maxn+10][maxn+10][3][3];
void dfs(int l,int r){
    if(l+1==r){
        dp[l][r][0][1]=dp[l][r][1][0]=dp[l][r][0][2]=dp[l][r][2][0]=1;
    }
    else if(match[l]==r){
        dfs(l+1,r-1);
        for(size_t lc{0};lc<=2;lc++){
            for(size_t rc{0};rc<=2;rc++){
                if(lc!=1)dp[l][r][1][0]=(dp[l][r][1][0]+dp[l+1][r-1][lc][rc])%p;
                if(lc!=2)dp[l][r][2][0]=(dp[l][r][2][0]+dp[l+1][r-1][lc][rc])%p;
                if(rc!=1)dp[l][r][0][1]=(dp[l][r][0][1]+dp[l+1][r-1][lc][rc])%p;
                if(lc!=1)dp[l][r][0][2]=(dp[l][r][0][2]+dp[l+1][r-1][lc][rc])%p;
            }
        }
    }
    else{
        dfs(l,match[l]);
        dfs(match[l]+1,r);
        for(size_t lc1{0};lc1<=2;lc1++){
            for(size_t rc1{0};rc1<=2;rc1++){
                for(size_t lc2{0};lc2<=2;lc2++){
                    for(size_t rc2{0};rc2<=2;rc2++){
                        if((rc1!=lc2)||((rc1==0)&&(lc2==0))){
                            dp[l][r][lc1][rc2]=(dp[l][r][lc1][rc2]+1ll*dp[l][match[l]][lc1][rc1]*dp[match[l]+1][r][lc2][rc2]%p)%p;
                        }
                    }
                }
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>s;
    for(size_t i{0};i<s.size();i++){
        if(s[i]=='(')st.push(i);
        if(s[i]==')'){
            match[st.top()]=i;
            st.pop();
        }
    }
    dfs(0,s.size()-1);
    int ans=0;
    for(size_t lc{0};lc<=2;lc++){
        for(size_t rc{0};rc<=2;rc++){
            ans=(ans+dp[0][s.size()-1][lc][rc])%p;
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
