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
constexpr int maxn=1e5;
// int fa[maxn+100],siz[maxn+100];
int p[maxn+100];
bool flag[maxn+100];
// int findf(int x){
//     return (fa[x]==x)?x:(fa[x]=findf(fa[x]));
// }
// void merge(int x,int y){
//     x=findf(x);y=findf(y);
//     if(x==y)return ;
//     fa[x]=y;
//     siz[y]+=siz[x];
//     return ;
// }
int main(){
    // freopen("boom3.in","r",stdin);
    // freopen("boom.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie();
    int n;
    cin>>n;
    // for(int i{1};i<=n;i++){
    //     fa[i]=i;
    //     siz[i]=1;
    // }
    int ans=n;
    for(int i{1};i<=n;i++){
        cin>>p[i];
        // merge(i,p);
        // ans-=siz[findf(i)];
        // siz[findf(i)]=0;
        // cout<<ans<<" ";
    }
    for(int i{1};i<=n;i++){
        int x=i;
        while(flag[x]==0){
            ans--;
            flag[x]=1;
            x=p[x];
        }
        cout<<ans<<" ";
    }
    cout.flush();
    return 0;
}
