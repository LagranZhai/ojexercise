#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1000,maxm=1000;
struct Edge{
    int v{},nxt{};
}edg[maxn*maxn+4*maxn];
int head[maxn*10],cnt{0};
int dp[maxn*10];
int id[maxn*10];
void addedge(int u,int v){
    id[v]++;
    edg[++cnt].nxt=head[u];
    edg[cnt].v=v;
    head[u]=cnt;
}
int nodetocnt[maxn+10];
std::unordered_set<int> isreal;
int maxp{0};
void build(int p,int cl,int cr){
    maxp=std::max(maxp,p);
    if(cl==cr){
        nodetocnt[cl]=p;
        isreal.insert(p);
        return ;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    addedge(p,p*2);
    addedge(p,p*2+1);
}
void modify(int p,int cl,int cr,int l,int r,int from){
    if(cl>=l&&cr<=r){
        addedge(from,p);
        return ;
    }
    if(cl!=cr){
        int mid=(cl+cr)/2;
        if(l<=mid)modify(p*2,cl,mid,l,r,from);
        if(r>mid)modify(p*2+1,mid+1,cr,l,r,from);
        return ;
    }
    return ;
}
int n,m;
std::vector<int> train[maxn+10];
int ans{0};
void toposort(){
    std::queue<int> q;
    for(int i{1};i<=maxp;i++){
        if(id[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur{q.front()};
        q.pop();
        for(int e{head[cur]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(isreal.find(to)!=isreal.end()){
                dp[to]=std::max(dp[to],dp[cur]+1);
                ans=std::max(ans,dp[to]);
            }
            dp[to]=std::max(dp[to],dp[cur]);
            id[to]--;
            if(id[to]==0){
                q.push(to);
            }
        }
    }
}
void bfs(int x){
    std::queue<int> q;
    q.push(x);
    while(!q.empty()){
        int cur{q.front()};
        q.pop();
        for(int e{head[cur]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(isreal.find(to)!=isreal.end()){
                dp[to]=std::max(dp[to],dp[cur]+1);
                ans=std::max(ans,dp[to]);
            }
            dp[to]=std::max(dp[to],dp[cur]);
            q.push(to);
        }
    }
}
int main(){
    // freopen("P1983_2.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    int s,t;
    for(int i{1};i<=m;i++){
        cin>>s;
        for(int j{1};j<=s;j++){
            cin>>t;
            train[i].push_back(t);
        }
    }
    build(1,1,n);
    for(int i{1};i<=m;i++){
        int stop{++maxp};
        int nostop{++maxp};
        for(int j:train[i]){
            addedge(nodetocnt[j],stop);
        }
        int last{train[i][0]};
        for(int k{1};k<train[i].size();k++){
            int j{train[i][k]};
            if(j-1>=last+1){
                modify(1,1,n,last+1,j-1,stop);
            }
            last=j;
        }
        // addedge(stop,stop);
    }
    maxp++;
    for(int i{1};i<=n;i++){
        addedge(maxp,nodetocnt[i]);
    }
    toposort();
    // cout<<maxp<<" "<<cnt<<"\n";
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}