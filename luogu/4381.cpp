#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=1e6;
#define int long long
int n;
struct Edge{
    int v,nxt,w;
}edg[maxn*3];
int head[maxn*2],cnt{1};
void addedge(int u,int v,int w){
    edg[++cnt]={v,head[u],w};
    head[u]=cnt;
}
std::vector<std::vector<int> > circle;
int ccnt{-1};
int st[maxn*2];
int dfs(int x,int fe){
    if(st[x]==1){
        ccnt++;
        circle.push_back({});
        return x;
    }
    if(st[x]==2){
        return 0;
    }
    st[x]=1;
    int flag{0};
    for(int e{head[x]};e;e=edg[e].nxt){
        if(e==(fe^1))continue;
        int to{edg[e].v};
        int t=dfs(to,e);
        if(t){
            circle[ccnt].push_back(e);st[x]=2;
            flag=(x==t)?0:t;
        }
    }
    return flag;
}
int d[maxn*2];
int sd[maxn*2];
int dfs1(int x,int f,int &ans){
    int dep{0};
    // int depmax{0};
    int d1{0},d2{0};
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(st[to]==2||to==f){
            continue;
        }
        int t=dfs1(to,x,ans)+edg[e].w;
        // depmax=std::max(vmax,depmax);
        dep=std::max(dep,t);
        if(t>=d1){
            d2=d1;d1=t;
        }
        else if(t>d2){
            d2=t;
        }
    }
    ans=std::max(ans,d1+d2);
    return dep;
}
// int sum[maxn*2];
struct Node{
    int index,val;
};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    int v,w;
    for(int i{1};i<=n;i++){
        cin>>v>>w;
        addedge(i,v,w);
        addedge(v,i,w);
    }
    for(int i{1};i<=n;i++){
        if(!st[i]){
            dfs(i,0);
        }
    }
    // for(int i{1};i<=n;i++){
    //     std::cerr<<st[i]<<" ";
    // }
    int ans{0};
    // const int nn=circle.size();
    for(auto c:circle){
        std::reverse(std::begin(c),std::end(c));
        int m{c.size()};
        int res{0};
        int sum{0};
        for(auto e:c){
            // cout<<edg[e].v<<" ";s
            d[edg[e].v]=dfs1(edg[e].v,0,sd[edg[e].v]);
            res=std::max(res,sd[edg[e].v]);
            sum+=edg[e].w;
        }
        int pre{0};
        std::deque<Node> q;
        for(int i{0};i<c.size();i++){
            // cout<<edg[c[i]].v<<" ";
            pre=pre+edg[c[i]].w;
            while(!q.empty()&&q.back().val<sum-pre+d[edg[c[i]].v])q.pop_back();
            q.push_back({i+1,sum-pre+d[edg[c[i]].v]});
        }
        pre=0;
        for(int i{0};i<c.size();i++){
            while(!q.empty()&&(i+1+m-q.front().index>=m))q.pop_front();
            pre+=edg[c[i]].w;
            int tmp{pre+d[edg[c[i]].v]+q.front().val};
            res=std::max(res,tmp);
            while(!q.empty()&&q.back().val<d[edg[c[i]].v]-pre)q.pop_back();
            q.push_back({i+1+m,d[edg[c[i]].v]-pre});
        }
        ans+=res;
        // cout<<res<<" ";
    }
    // for(int i{1};i<=n;i++){
    //     cout<<d[i]<<" ";
    // }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}