#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<stack>
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
constexpr int maxn=1e5,maxm=5e5;
#define int long long
int head[maxn*2],cnt=0;
struct Edge{
    int v=0,nxt=0;
}edg[maxm*3];
void addedge(int u_,int v_){
    edg[++cnt].v=v_;
    edg[cnt].nxt=head[u_];
    head[u_]=cnt;
}
int n,m;
int dfn[maxn*2],low[maxn*2],siz[maxn*2],tot=0,ur[maxn*2];
bool cut[maxn*2];
void tarjan(int x,int f){
    low[x]=dfn[x]=++tot;
    int child=0;
    siz[x]+=1;
    int svs=0;
    for(int e=head[x];e;e=edg[e].nxt){
        int to=edg[e].v;
        if(dfn[to]==0){
            child++;
            tarjan(to,x);
            low[x]=min(low[x],low[to]);
            siz[x]+=siz[to];
            if(low[to]>=dfn[x]&&x!=f){
                cut[x]=1;
            }
            if(low[to]>=dfn[x]){
                svs+=siz[to];
                ur[x]+=siz[to]*(n-siz[to]);
            }
        }
        else if(dfn[to]<dfn[x]&&to!=f){
            low[x]=min(dfn[to],low[x]);
        }
    }
    if(child>1&&x==f){
        cut[x]=1;
    }
    if(!cut[x]){
        ur[x]=2*(n-1);
    }
    else{
        ur[x]+=(n-svs-1)*(svs+1)+n-1;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
{
    int u,v;
    for(int i{1};i<=m;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
}
    tarjan(1,1);
    for(int i{1};i<=n;i++){
        cout<<ur[i]<<"\n";
    }
    cout.flush();
    return 0;
}
