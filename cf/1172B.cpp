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
constexpr int maxn=2e5,p=998244353;
struct Edge{
    int v{0},nxt{0};
}edg[maxn*3];
int head[maxn+100],cnt=0,deg[maxn+100];
void addedge(int u_,int v_){
    edg[++cnt].v=v_;
    edg[cnt].nxt=head[u_];
    head[u_]=cnt;
}
void dfs(int x,int f){
    deg[x]=0;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to=edg[e].v;
        if(to!=f){
            deg[x]++;
            dfs(to,x);
        }
    }
}
int n;
int fac[maxn+100];
void init(int n){
    fac[0]=1;
    fac[1]=1;
    for(int i{2};i<=n;i++){
        fac[i]=(fac[i-1]*i)%p;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    init(n);
    dfs(1,0);
    int ans=1;
    for(int i{1};i<=n;i++){
        ans=(ans*fac[deg[i]])%p;
    }
    cout<<(ans*n)%p<<"\n";
    cout.flush();
    return 0;
}
