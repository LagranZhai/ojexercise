#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e6;
#define int long long
struct Edge{
    int v{0},nxt{0};
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
    return ;
}
int n;
int a[maxn*2];
std::vector<int> node;
bool vis[maxn*2];
auto dfs(int x,int f){
    node.push_back(x);
    vis[x]=1;
    int fecnt{1};//fanxiang bian exist,but only one
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to==f&&fecnt==1){
            fecnt--;
            continue;
        }
        if(vis[to]){
            return std::make_pair(x,to);
        }
        auto tmp{dfs(to,x)};
        if(tmp!=std::make_pair<int,int>(0ll,0ll)){
            return tmp;
        }
    }
    return std::make_pair(0ll,0ll);
}
int dp[maxn+100][2];
void dfs1(int x,int f,int rt1,int rt2){
    dp[x][0]=0;
    dp[x][1]=((x!=rt2)?a[x]:std::numeric_limits<int>::min());
    int fecnt{1};
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            if(((x==rt1&&to==rt2)||(x==rt2&&to==rt1))&&fecnt==1){
                fecnt--;
                continue;
            }
            dfs1(to,x,rt1,rt2);
            dp[x][0]+=std::max(dp[to][0],dp[to][1]);
            dp[x][1]+=dp[to][0];
        }
    }
}
void dfs3(int x,int f){
    vis[x]=1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&!vis[to]){
            dfs3(to,x);
        }
    }
}
std::vector<int> block;
void getblock(){
    for(int i{1};i<=n;i++){
        if(!vis[i]){
            dfs3(i,0);
            block.push_back(i);
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    int t;
    for(int i{1};i<=n;i++){
        cin>>a[i]>>t;
        addedge(i,t);addedge(t,i);
    }
    getblock();
    std::fill(vis,vis+maxn*2,0);
    int ans{0};
    for(int a:block){
        auto [rt1,rt2]=dfs(a,0);
        // cout<<rt1<<" "<<rt2<<"\n";
        int cur{0};
        dfs1(rt1,0,rt1,rt2);
        cur=std::max({cur,dp[rt1][1],dp[rt1][0]});
        dfs1(rt2,0,rt2,rt1);
        cur=std::max({cur,dp[rt2][1],dp[rt2][0]});
        ans+=cur;
        for(int b:node){
            vis[b]=0;
        } 
        node.clear();
    }
    cout<<ans<<std::endl;
    cout.flush();
    return 0;
}