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
constexpr int maxn=1e6,maxm=2e6;
int n,m;
int head[maxn*2],cnt=1;
struct Edge{
    int v=0,nxt=0;
}edg[maxm*3];
void addedge(int u_,int v_){
    edg[++cnt].v=v_;
    edg[cnt].nxt=head[u_];
    head[u_]=cnt;
}
int dfn[maxn+100],low[maxn+100],idx=0;
int ans=0;
void tarjan(int x,int fe){
    dfn[x]=low[x]=++idx;
    int child=0;
    int flag=0;
    for(int e=head[x];e;e=edg[e].nxt){
        int to=edg[e].v;
        if(!dfn[to]){
            child++;
            tarjan(to,e);
            low[x]=min(low[x],low[to]);
        }
        else if(e!=(fe^1)){
            ans++;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
{
    int u,v;
    for(int i{1};i<=m;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
}
    for(int i{1};i<=n;i++){
        if(!dfn[i])tarjan(i,cnt+10);
    }
    cout<<ans/2<<"\n";
    cout.flush();
    return 0;
}
