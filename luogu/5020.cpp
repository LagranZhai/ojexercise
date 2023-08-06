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
constexpr int maxn=100,maxm=25000;
int n;
int dp[maxm+100];
std::vector<int > a;
void solve(){
    int amax=*std::max_element(std::begin(a),std::end(a));
    int amin=*std::max_element(std::begin(a),std::end(a));
    std::fill(dp,dp+maxm+100,0);
    dp[0]=1;
    for(int i{0};i<a.size();i++){
        for(int j{0};j+a[i]<=amax;j++){
            if(dp[j])dp[j+a[i]]+=1;
        }
    }
    int ans=a.size();
    for(int i{0};i<a.size();i++){
        if(dp[a[i]]>1)ans--;
    }
    cout<<ans<<"\n";
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int T;
    cin>>T;
    while(T--){
        a.clear();
        cin>>n;
        {
            int t;
            for(int i{1};i<=n;i++){
                cin>>t;
                a.push_back(t);
            }
        }

        solve();
    }
    cout.flush();
    return 0;
}
