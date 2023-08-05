#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<set>
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
constexpr int maxn=1e5,maxm=1e6;
int n,m;
int head[maxn+100],cnt=0;
struct Edge{
    int v=0,nxt=0;
}edg[maxm*2+100];
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
}
int deg[maxn*2];
std::set<std::pair<int,int > > q;
int bh[maxn*2],bhcnt=0;
void dfs(int x,int num){
    bh[x]=num;
    for(int e=head[x];e;e=edg[e].nxt){
        int to=edg[e].v;
        if(!bh[to])dfs(to,num);
    }
}
int solve(int now){
    q.clear();
    for(int i{1};i<=n;i++){
        if(bh[i]==now){
            q.insert(std::make_pair(deg[i],i));
        }
    }
    int ans=0;
    while(!q.empty()){
        auto it=q.begin();
        int d=(*it).first;
        int p=(*it).second;
        //cout<<p<<" "<<d<<"\n";
        q.erase(it);
        deg[p]=0;
        cout<<d<<" ";
        ans=max(d,ans);
        for(int e=head[p];e;e=edg[e].nxt){
            int to=edg[e].v;
            if(deg[to]){
                q.erase(std::make_pair(deg[to],to));
                --deg[to];
                q.insert(std::make_pair(deg[to],to));
            }
        }
    }
    return ans;
}
int main(){
    freopen("graph3.in","r",stdin);
    freopen("graph3.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
    int x,y;
    for(int i{1};i<=m;i++){
        cin>>x>>y;
        deg[x]++;deg[y]++;
        addedge(x,y);addedge(y,x);
    }
    for(int i{1};i<=n;i++){
        if(!bh[i]){
            ++bhcnt;
            dfs(i,bhcnt);
        }
    }
    int ans=0;
    for(int i=1;i<=bhcnt;i++){
        ans=max(ans,solve(i));
    }
    cout<<ans<<"\n";
    cout<<"\n";
    cout.flush();
    return 0;
}
