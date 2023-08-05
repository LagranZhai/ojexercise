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
constexpr int maxn=4e5,maxm=2e5;
int n,m,k,cnt=0;
struct Edge{
    int v,nxt;
}edg[maxm*3];
int head[maxn+100];
std::vector<int > des;
bool vdes[maxn+100];
int fa[maxn+100];
int findf(int x){
    return fa[x]==x?x:(fa[x]=findf(fa[x]));
}
void addedge(int u_,int v_){
    edg[++cnt].v=v_;
    edg[cnt].nxt=head[u_];
    head[u_]=cnt;
    return ;
}
int merge(int x,int y){
    int fx=findf(x),fy=findf(y);
    if(fx==fy)return 0;
    fa[fy]=fx;
    return 1;
}
std::vector<int > ans;
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
    int co=n;
{
    int u,v;
    for(int i{1};i<=m;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
}
    
    cin>>k;
{
    int t;
    for(int i{1};i<=k;i++){
        cin>>t;
        vdes[t]=1;
        des.push_back(t);
    }
}
    for(int i{0};i<=n;i++)fa[i]=i;
    for(int i=0;i<n;i++){
        if(vdes[i])continue;
        for(int e=head[i];e;e=edg[e].nxt){
            int to=edg[e].v;
            if(vdes[to])continue;
            co-=merge(i,to);
        }
    }
    ans.push_back(co-k);
    for(int i=k-1;i>=0;i--){
        vdes[des[i]]=0;
        for(int e=head[des[i]];e;e=edg[e].nxt){
            int to=edg[e].v;
            if(!vdes[to])co-=merge(des[i],to);
        }
        ans.push_back(co-i);
    }
    for(int i=ans.size()-1;i>=0;i--){
        cout<<ans[i]<<"\n";
    }
    cout.flush();
    return 0;
}
