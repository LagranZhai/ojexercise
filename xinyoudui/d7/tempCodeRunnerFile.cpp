//PE
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=5e5+100,maxm=5e6;
struct Edge{
    int v,nxt,w;
}edg[maxm*2];
int head[maxn],ecnt{0};
void addedge(int u,int v,int w){
    edg[++ecnt]={v,head[u],w};
    head[u]=ecnt;
}
int n,m;
std::queue<int > q;
bool inq[maxn*2];
int dis[maxn*2];
int cnt[maxn*2];
bool spfa(int n,int s){
    std::fill(dis,dis+maxn*2,std::numeric_limits<signed >::max());
    std::fill(inq,inq+maxn*2,false);
    std::fill(cnt,cnt+maxn*2,0);
    q=std::queue<int >{};
    dis[s]=0;
    inq[s]=true;
    cnt[s]=1;
    q.push(s);
    while(!q.empty()){
        int cur{q.front()};
        q.pop();
        inq[cur]=0;
        for(int e{head[cur]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(dis[to]>dis[cur]+edg[e].w){
                dis[to]=dis[cur]+edg[e].w;
                cnt[to]=cnt[cur]+1;
                if(cnt[to]>n)return true;
                if(!inq[to]){
                    q.push(to);
                    inq[to]=1;
                }
            }
        }
    }
    return false;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int k,u,v;
    for(int i{1};i<=n;i++){
        cin>>k;
        addedge(i-1,i,k);
    }
    for(int i{1};i<=m;i++){
        cin>>u>>v>>k;
        addedge(v,u-1,-k);
    }
    spfa(n+1,n);
    cout<<-1*dis[0]<<"\n";
    cout.flush();
    return 0;
}