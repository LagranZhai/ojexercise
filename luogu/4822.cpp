#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<queue>
#include<vector>
#include<limits>
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
constexpr int maxn=50,maxm=1e3;
int n,m,k;
struct Edge
{
    int v=0,w=0,nxt=0;
}edg[maxm*maxn*5];
int head[maxn*maxn+100],cnt=0;
void addedge(int u_,int v_,int w_){
    edg[++cnt].v=v_;
    edg[cnt].w=w_;
    edg[cnt].nxt=head[u_];
    head[u_]=cnt;
}
struct Cmp{
    bool operator()(const std::pair<int,int >& a,const std::pair<int,int >& b){
        return a.first>b.first;
    }
};
int dis[maxn*maxn+100];
bool vis[maxn*maxn+100];
void dijkstra(int s){
    std::fill(dis,dis+maxn*maxn+100,std::numeric_limits<int >::max());
    std::priority_queue<std::pair<int,int >,std::vector<std::pair<int,int > >,Cmp > q;
    dis[s]=0;
    q.push(std::make_pair(0,s));
    while(!q.empty()){
        int cur=q.top().second;
        q.pop();
        if(!vis[cur]){
            vis[cur]=1;
            for(int e=head[cur];e;e=edg[e].nxt){
                int to=edg[e].v;
                if(!vis[to]){
                    dis[to]=min(dis[to],dis[cur]+edg[e].w);
                    q.push(std::make_pair(dis[to],to));
                }
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m>>k;
{
    int u,v,w;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>w;
        for(int j{0};j<=k;j++){
            addedge(j*n+u,j*n+v,w);
            addedge(j*n+v,j*n+u,w);
            if(j!=k){
                addedge(j*n+u,(j+1)*n+v,w/2);
                addedge(j*n+v,(j+1)*n+u,w/2);
            }
        }
    }
}
    dijkstra(1);
    int ans=std::numeric_limits<int >::max();
    for(int i{0};i<=k;i++){
        ans=min(ans,dis[i*n+n]);
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
