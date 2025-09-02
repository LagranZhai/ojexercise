//PB
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=300,p=1e9+7;
struct Edge{
    int v,nxt,u;
}edg[maxn*2];
int head[maxn],cnt{0};
void addedge(int u,int v){
    edg[++cnt]={v,head[u],u};
    head[u]=cnt;
}
int n,m,k;
int dfn[maxn],low[maxn],dfx{0},id[maxn];
std::stack<Edge> s;
using pii=std::pair<int,int>;
pii siz[maxn]{{}};
int vcc{0};
void tarjan(int x,int f){
    dfn[x]=low[x]=++dfx;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            if(dfn[to]){
                s.push(edg[e]);
                low[x]=std::min(low[x],dfn[to]);
            }
            else{
                s.push(edg[e]);
                tarjan(to,x);
                low[x]=std::min(low[to],low[x]);
                if(low[to]>=dfn[x]){
                    vcc++;
                    while(1){
                        siz[vcc].first++;
                        if(id[s.top().u]!=vcc){
                            id[s.top().u]=vcc;
                            siz[vcc].second++;
                        }
                        if(id[s.top().v]!=vcc){
                            id[s.top().u]=vcc;
                            siz[vcc].second++;
                        }
                        if(s.top().u==x&&s.top().v==to){
                            s.pop();break;
                        }
                        s.pop();
                    }
                }
            }
        }
    }
}
int fac[maxn],inv[maxn];
int qpow(int a,int b){
    int c{1};
    while(b){
        if(b&1)c=c*a%p;
        a=a*a%p;
        b>>=1;
    }
    return c;
}
int phi[maxn];
std::vector<int> pri;
bool vis[maxn];
void euler(){
    phi[1]=0;
    for(int i{2};i<maxn;i++){
        if(!vis[i]){
            pri.push_back(i);
        }
        for(int a:pri){
            if(a*i>=maxn)continue;
            if(i%a==0){
                vis[i*a]=1;
                phi[i*a]=phi[i]*a;
                break;
            }
            else{
                vis[i*a]=1;
                phi[i*a]=phi[i]*(a-1);
            }
        }
    }
}
int burn(int x){
    int res{0},base{k};
    for(int i{1};i<=x;i++){
        if(x%i==0){
            res=(res+base*phi[x/i]%p)%p;
        }
        base=base*k%p;
    }
    return res*inv[x]%p*fac[x-1]%p;
}
int chose(int x,int y){
    return fac[x]*inv[y]%p*inv[x-y]%p;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m>>k;
    int u,v;
    for(int i{1};i<=m;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
    for(int i{1};i<=n;i++){
        if(!dfn[i])tarjan(i,0);
    }
    fac[0]=1;
    for(int i{1};i<maxn;i++){
        fac[i]=fac[i-1]*i%p;
    }
    inv[maxn-1]=qpow(fac[maxn-1],p-2);
    for(int i{maxn-2};i>=0;i--){
        fac[i]=fac[i+1]*(i+1)%p;
    }
    euler();
    int ans{1};
    for(int i{1};i<=vcc;i++){
        if(siz[i].second>siz[i].first){
            ans=ans*k%p;
        }
        if(siz[i].second==siz[i].first){
            ans=ans*burn(siz[i].second)%p;
        }
        if(siz[i].second<siz[i].first){
            ans=ans*chose(siz[i].first+k-1,k-1)%p;
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}