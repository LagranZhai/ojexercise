#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int maxn=3e5,maxm=3e5;
int dis[maxn*2];
bool vis[maxn*2];
struct Graph{
    struct Edge{
        int v{0},nxt{0},w{0},index{0};
    }edg[maxm*3];
    int head[maxn*2],cnt{0};
    void addedge(int u,int v,int w,int index){
        edg[++cnt].v=v;
        edg[cnt].w=w;
        edg[cnt].index=index;
        edg[cnt].nxt=head[u];
        head[u]=cnt;
    }
}g1{},g2{};
struct Node{
    int dis{0},p{0},f{0},index{0};
    bool operator<(const Node A)const{
        return dis>A.dis;
    }
};
void dijkstra(){
    std::fill(dis,dis+maxn*2,std::numeric_limits<int>::max()>>3);
    dis[1]=0;
    std::priority_queue<Node> q;
    q.push({0,1,0,0});
    while(!q.empty()){
        Node cur{q.top()};
        q.pop();
        if(!vis[cur.p]){
            g2.addedge(cur.f,cur.p,0,cur.index);
            g2.addedge(cur.p,cur.f,0,cur.index);
            vis[cur.p]=1;
            for(int e{g1.head[cur.p]};e;e=g1.edg[e].nxt){
                int to{g1.edg[e].v};
                if(!vis[to]&&dis[to]>dis[cur.p]+g1.edg[e].w){
                    dis[to]=dis[cur.p]+g1.edg[e].w;
                    q.push({dis[to],to,cur.p,g1.edg[e].index});
                }
            }
        }
    }
}
std::vector<int> selected;
int tot{0};
bool dfs(int x,int f){
    tot--;
    if(tot==0){
        return false;
    }
    for(int e{g2.head[x]};e;e=g2.edg[e].nxt){
        int to{g2.edg[e].v};
        if(to!=f){
            selected.push_back(g2.edg[e].index);
            if(!dfs(to,x)){
                return false;
            }
        }
    }
    return true;
}
int n,m,k;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>k;
    int u,v,w;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>w;
        g1.addedge(u,v,w,i);
        g1.addedge(v,u,w,i);
    }
    dijkstra();
    tot=std::min(n,k+1);
    dfs(1,0);
    cout<<selected.size()<<"\n";
    for(int a:selected){
        cout<<a<<" ";
    }
    cout.flush();
    return 0;
}