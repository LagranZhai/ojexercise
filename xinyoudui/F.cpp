#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e4,maxm=1e4;
#define int long long
struct Edge{
    int v{0},nxt{0},w{0};
}edg[maxm*2];
int head[maxn*2],ecnt{0};
void addedge(int u,int v,int w){
    edg[++ecnt].v=v;
    edg[ecnt].w=w;
    edg[ecnt].nxt=head[u];
    head[u]=ecnt;
    return ;
}
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
    int n,m;
    cin>>n>>m;
    int a,b,c;
    for(int i{};i<m;i++){
        cin>>a>>b>>c;
        addedge(a,b,c);
    }
    for(int i{1};i<=n;i++){
        addedge(n+1,i,0);
    }
    cout<<(spfa(n+1,n+1)?"NO":"YES")<<"\n";
    cout<<std::flush;
    return 0;
}