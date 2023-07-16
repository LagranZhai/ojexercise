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
constexpr int maxn=5e4;
int n,k;
struct Edge {
    int v=0,nxt=0;
}edg[maxn*3];
int head[maxn*2],cnt=0;
void addedge(int u_,int v_) {
    edg[++cnt].v=v_;
    edg[cnt].nxt=head[u_];
    head[u]=cnt;
}
namespace tcd{
    int fa[maxn*2],depth[maxn*2];
    void dfs1(int x,int f){
        fa[x]=f;
        depth[x]=depth[f]+1;
        for(int e=head[x];e;e=edg[e].nxt){
            if(edg[e].v!=f)dfs1(edg[e].v,x);
        }
        return ;
    }
}
int fa[maxn*2],depth[maxn*2];
void dfs1(int x,int f){
    fa[x]=f;
    depth[x]=depth[f]+1;
    for(int e=head[x];e;e=edg[e].nxt){
        if(edg[e].v!=f)dfs1(edg[e].v,x);
    }
    return ;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>k;
{
    int a,b;
    for(int i{1};i<=n-1;i++){
        cin>>a>>b;
        addedge(a,b);
        addedge(b,a);
    }
}
    dfs(1,0);
    for(int i{1};i<=k;i++){

    }
    cout.flush();
    return 0;
}
