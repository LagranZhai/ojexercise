#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5,maxm=4e6;
#define int long long
struct Edge{
    int v,w,nxt;
}edg[maxm];
int head[maxn*9],cnt{0};
void addedge(int u,int v,int w){
    edg[++cnt]={v,w,head[u]};
    head[u]=cnt;
    return ;
}
int tot{0};
int inode_to_cnt[maxn*2],onode_to_cnt[maxn*2];
void build(int p,int cl,int cr,int *ntc,const std::function<void(int,int)> &myadd,int d){
    if(cl==cr){
        tot=std::max(tot,p+d);
        ntc[cl]=p+d;
        return ;
    }
    int mid{(cl+cr)/2};
    build(p*2,cl,mid,ntc,myadd,d);
    build(p*2+1,mid+1,cr,ntc,myadd,d);
    myadd(p+d,p*2+d);
    myadd(p+d,p*2+1+d);
    return ;
}
void rangeadd(int p,int cl,int cr,const int l,const int r,const int from,const std::function<void(int,int)> &myadd,int d){
    if(cl>=l&&cr<=r){
        myadd(from,p+d);
        return;
    }
    if(cl!=cr){
        int mid{(cl+cr)/2};
        if(l<=mid)rangeadd(p*2,cl,mid,l,r,from,myadd,d);
        if(r>mid)rangeadd(p*2+1,mid+1,cr,l,r,from,myadd,d);
        return ;
    }
}
int dis[maxn*9];
struct Node{
    int dis,p;
};
bool vis[maxn*9];
void dijkstra(int s){
    std::fill(dis,dis+tot+10,std::numeric_limits<int>::max());
    std::fill(vis,vis+tot+10,0);
    auto cmp=[](const Node A,const Node B)->bool{return A.dis>B.dis;};
    std::priority_queue<Node,std::vector<Node> ,decltype(cmp)> q(cmp);
    using tii=std::tuple<int,int,int>;
    auto cmp1=[](const tii A,const tii B)->bool{return std::get<0>(A)<std::get<0>(B);};
    std::priority_queue<tii,std::vector<tii>,decltype(cmp1)> q1(cmp1);
    q.push({0,s});
    dis[s]=0;
    while(!q.empty()){
        int cur{q.top().p};
        q.pop();
        if(vis[cur])continue;
        vis[cur]=1;
        for(int e{head[cur]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(!vis[to]&&dis[to]>dis[cur]+edg[e].w){
                dis[to]=dis[cur]+edg[e].w;
                q.push({dis[to],to});
            }
        }
    }
}
int n,q,s;
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>q>>s;
    auto addpositive{[&](int w){return std::bind(addedge,std::placeholders::_1,std::placeholders::_2,w);}};
    auto addnegative{[&](int w){return std::bind(addedge,std::placeholders::_2,std::placeholders::_1,w);}};
    build(1,1,n,inode_to_cnt,addpositive(0),0);
    int tsiz{tot};
    build(1,1,n,onode_to_cnt,addnegative(0),tsiz);
    for(int i{1};i<=n;i++){
        addedge(inode_to_cnt[i],onode_to_cnt[i],0);
        addedge(onode_to_cnt[i],inode_to_cnt[i],0);
        // std::cout<<inode_to_cnt[i]<<" "<<onode_to_cnt[i]<<"\n";
    }
    // std::cout<<tot<<"\n";
    int u,v,w,l,r;int opt;
    for(int i{1};i<=q;i++){
        cin>>opt;
        if(opt==1){
            cin>>v>>u>>w;
            addedge(onode_to_cnt[v],inode_to_cnt[u],w);
        }
        if(opt==2){
            cin>>v>>l>>r>>w;
            rangeadd(1,1,n,l,r,onode_to_cnt[v],addpositive(w),0);
        }
        if(opt==3){
            cin>>v>>l>>r>>w;
            rangeadd(1,1,n,l,r,inode_to_cnt[v],addnegative(w),tsiz);
        }
    }
    // std::cerr<<"a";
    dijkstra(onode_to_cnt[s]);
    for(int i{1};i<=n;i++){
        cout<<((dis[inode_to_cnt[i]]==(std::numeric_limits<int>::max()))?-1:dis[inode_to_cnt[i]])<<" ";
    }
    cout.flush();
    return 0;
}