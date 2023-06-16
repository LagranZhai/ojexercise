#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
using std::cin,std::ios,std::max,std::min;
constexpr int maxn=2000,maxm=75;
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
//Myos<std::ostream&> t{std::cout};
Myos<std::ostringstream> t{std::ostringstream()};
auto& cout = t.mys;
int n,ch[maxn*maxm][maxm+10],tot=1;
bool cnt[maxn*maxm];
int insert(const std::string &s){
    int p=1,cur=0;
    for(int i{0};i<s.size();i++){
        if(ch[p][s[i]-'a']==0)ch[p][s[i]-'a']=++tot;
        p=ch[p][s[i]-'a'];
        if(cnt[p])cur++;
    }
    cnt[p]=1;
    return cur;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    std::string t;
    int ans=0;
    for(int i{1};i<=n;i++){
        cin>>t;
        ans=max(ans,insert(t));
    }
    cout<<ans<<"\n";
    return 0;
}
