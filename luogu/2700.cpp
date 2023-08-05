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
constexpr int maxn=1e5;
#define int long long
int fa[maxn+100];
bool enemy[maxn];
int findf(int x){
    return (fa[x]==x)?x:(fa[x]=findf(fa[x]));
}
void merge(int u,int v){
    u=findf(u);v=findf(v);
    if(u!=v){
        fa[v]=u;
        if(enemy[v])enemy[u]=1;
    }
}
struct Edge{
    int u,v,w;
}edg[maxn+100];
int tot=0;
int n,k;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>k;
{
    int p;
    for(int i{1};i<=k;i++){
        cin>>p;
        enemy[p]=1;
    }
}
    int sum=0;
    for(int i{1};i<n;i++){
        ++tot;
        cin>>edg[tot].u>>edg[tot].v>>edg[tot].w;
        sum+=edg[tot].w;
    }
    std::sort(edg+1,edg+n,[](const Edge& a,const Edge& b)->bool{
        return a.w>b.w;
    });
    for(int i{1};i<=n;i++){
        fa[i]=i;
    }
    int ans=sum;
    for(int i{1};i<n;i++){
        if(findf(edg[i].u)!=findf(edg[i].v)&&((!enemy[fa[edg[i].u]])||(!enemy[fa[edg[i].v]]))){
            merge(edg[i].u,edg[i].v);
            ans-=edg[i].w;
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}