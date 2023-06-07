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
        mys<<"t"<<std::flush;
    };
};
template<>
Myos<std::ostringstream>::~Myos()noexcept{
    std::cout<<"a"<<mys.str()<<std::flush;
}
//auto&& cout = Myos<std::ostringstream>(std::ostringstream()).mys;
auto&& cout = std::move(Myos<std::ostream&>(std::cout).mys);
constexpr int maxn=2000,maxm=27;
int n;
int tot=1,ch[maxn*maxm][maxm];
bool tag[maxn*maxm];
int insert(std::string t){
    int p=1,ans=0;
    for(int i{0};i<t.size();i++){
        if(ch[p][t[i]-'a']==0)ch[p][t[i]-'a']=++tot;
        p=ch[p][t[i]-'a'];
        if(tag[p])ans++;
    }
    tag[p]=1;
    return ans+1;
}
// void init(){

// }
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;std::string t;
    int maxans=0;
    for(int i{1};i<=n;i++){
        cin>>t;
        maxans=max(insert(t),maxans);
    }
    cout<<maxans<<"\n";
    return 0;
}
