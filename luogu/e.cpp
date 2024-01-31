#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=3e5;
int n,s,t;
struct Edge{
    int v{},nxt{};
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u]};
    head[u]=cnt;
}
int fa[maxn*2];
int leaf{0};
int siz[maxn*2];
void dfs(int x,int f){
    siz[x]=1;
    int child{0};
    fa[x]=f;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            child++;
            dfs(to,x);
            siz[x]+=siz[to];
        }
    }
    if(child==1&&f==0)leaf++;
    if(child==0)leaf++;
}
std::vector<int> bc;
int dp[maxn*2];
void dfs2(int x,int f,int g){
    dp[x]=0;
    std::priority_queue<int> son;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&to!=g){
            dfs2(to,x,g);
            son.push(dp[to]);
        }
    }
    if(son.empty()){
        dp[x]=0;
    }
    else{
        int scnt{1};
        while(!son.empty()){
            dp[x]=std::max(dp[x],son.top()+scnt);
            son.pop();
            scnt++;
        }
    }
}
int main(){
    // freopen("e.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>s>>t;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
    dfs(s,0);
    int cur{t};
    while(cur!=0){
        bc.push_back(cur);
        cur=fa[cur];
    }
    if(leaf==2){
        int l1=siz[t]-1,l2=bc.size()-2,l3=n-l1-bc.size();
        cout<<std::max({(l2-1)/2,l1,l3})<<"\n";
        // if(l3>std::max(l1,l2)*2){
        //     cout<<(l3+1)/2<<"\n";
        // }
        // else{
        //     cout<<std::max(l1,l2)<<"\n";
        // }
    }
    else{
        // for(int a:bc)cout<<a<<" ";
        // int l{0},r{bc.size()-2},mid{(l+r)/2};
        int ans{std::numeric_limits<int>::max()};
        for(int i{0};i<bc.size()-1;i++){
            dfs2(s,0,bc[i]);
            int t1=dp[s];
            dfs2(t,0,bc[i+1]); 
            int t2=dp[t];
            // if(std::max(t1,t2)>ans)break;
            ans=std::min(ans,std::max(t1,t2));
            // cout<<std::max(t1,t2)<<"\n";
        }
        cout<<ans<<"\n";
    }
    cout.flush();
    return 0;
}