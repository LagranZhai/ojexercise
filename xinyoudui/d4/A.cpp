//PA
#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
#define int long long
constexpr int maxn=20;
int n,m,k;
// int edge[maxn][maxn];
struct Edge{
    int u,v;
}edg[maxn*maxn];
int cnt{0};
int mi[maxn],base=10ll;
int check(int x,int st){
    return (st/mi[x-1])%base;
}
std::unordered_set<int> mp;
int dfs(int st){
    bool flag{1};
    int deg[11]{0};
    int sum{0};
//    if(st==11){
//    	std::cerr<<1;
//	}
    for(int i{1};i<=n;i++){
        deg[i]=check(i,st);
        if(deg[i]==0){
            flag=0;
        }
        else{
            if(deg[i]==1){
                sum++;
            }
        }
    }
    if(flag){
        if(sum==k){
            return 1;
        }
        else return 0;
    }
    if(sum>k){
        return 0;
    }   
    int res{0};
    for(int i{1};i<=cnt;i++){
        int u{edg[i].u},v{edg[i].v};
        if(deg[v]){
            std::swap(u,v);
        }
        if(deg[u]==0&&deg[v]==0){
            if(v==1){
                std::swap(u,v);
            }
        }
        if(((deg[u]==0&&u==1)||deg[u]>0)&&deg[v]==0){
            res+=dfs(st+(1*mi[u-1])+(1*mi[v-1]));
        }
    }
    return res/sum;
}
signed main(){
    // freopen("A.in","r",stdin);
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m>>k;
    int u,v;
    for(int i{1};i<=m;i++){
        cin>>u>>v;
        edg[++cnt]={u,v};
        // edg[++cnt]={v,u};
        // edge[u][v]=1;edge[v][u]=1;
    }
    mi[0]=1;
    for(int i{1};i<=n;i++){
        mi[i]=base*mi[i-1];
    }
    cout<<dfs(0)<<"\n";     
    cout.flush();
    return 0;
}
