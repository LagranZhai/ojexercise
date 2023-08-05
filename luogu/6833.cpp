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
constexpr int maxn=1e3;
using ll=long long;
struct Cmp{
    auto operator()(const std::pair<ll,int > a,const std::pair<ll,int > b)->bool{
        return a.first>b.first;
    }
};
int n,m,a,b,c;
ll r[(maxn+10)*(maxn+10)];
bool vis[(maxn+10)*(maxn+10)];
ll dis1[(maxn+10)*(maxn+10)],dis2[(maxn+10)*(maxn+10)],dis3[(maxn+10)*(maxn+10)];
void dijkstra(int s,ll *dis){
    std::fill(dis,dis+(maxn+10)*(maxn+10),std::numeric_limits<ll >::max());
    std::fill(vis,vis+(maxn+10)*(maxn+10),0);
    dis[s]=r[s];
    std::priority_queue<std::pair<ll,int >,std::vector<std::pair<ll,int > >,Cmp > q;
    q.push(std::make_pair(r[s],s));
    auto op=[&](int ord,int p){
        if(!vis[p]){
            dis[p]=min(dis[p],dis[ord]+r[p]);
            q.push(std::make_pair(dis[p],p));
        }
    };
    while(!q.empty()){
        int cur=q.top().second;
        q.pop();
        if(!vis[cur]){
            vis[cur]=true;
            if(cur%m!=1){
                op(cur,cur-1);
            }
            if(cur%m!=0){
                op(cur,cur+1);
            }
            if(cur+m<=n*m){
                op(cur,cur+m);
            }
            if(cur-m>0){
                op(cur,cur-m);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m>>a>>b>>c;
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            cin>>r[(i-1)*m+j];
        }
    }
    dijkstra(a,dis1);
    dijkstra((n-1)*m+b,dis2);
    dijkstra((n-1)*m+c,dis3);
    int ansi=0;
    ll ans=std::numeric_limits<ll >::max();
    for(int i{1};i<=n*m;i++){
        if(ans>dis1[i]+dis2[i]+dis3[i]-2*r[i]){
            ans=dis1[i]+dis2[i]+dis3[i]-2*r[i];
            ansi=i;
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
