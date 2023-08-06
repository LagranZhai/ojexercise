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
constexpr int maxn=5e5;
int head[maxn+100],cnt=0;
struct Edge{
    int v=0,nxt=0;
}edg[maxn*3];
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
}
int in[maxn*2],vis[maxn*2];
void dfs(int x){
    cout<<x<<" ";
    vis[x]=1;
    for(int e=head[x];e;e=edg[e].nxt){
        int to=edg[e].v;
        if(!vis[to]){
            dfs(to);
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int n;
    cin>>n;
{
    int u,v;
    for(int i{1};i<=n-1;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
        in[v]++;
        in[u]++;
    }
}
    int top=0;
    for(int i{1};i<=n;i++){
        if(in[i]==1){
            top=i;
            break;
        }
    }
    dfs(top);
    cout<<"\n";
    cout.flush();
    return 0;
}
