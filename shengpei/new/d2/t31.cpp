#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e5;
// #define int long long
int tcnt[maxn*4],tag[maxn*4];
long long tsum[maxn*4],a[maxn*2];
int n,q;
int head[maxn],cnt{0};
struct Edge{
    int nxt{0},v{0};
}edg[maxn*3];
void addedge(int u,int v){
    edg[++cnt].nxt=head[u];
    edg[cnt].v=v;
    head[u]=cnt;
    return ;
}
bool des[maxn];
int dfn[maxn*2],rnk[maxn*2],tot=0,siz[maxn*2];
void dfs(int x,int f){
    dfn[x]=++tot;
    siz[x]=1;
    rnk[tot]=x;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x);
            siz[x]+=siz[to];
        }
    }
    return ;
}

void build(int p,int cl,int cr){
    if(cl==cr){
        tcnt[p]=0;
        tsum[p]=a[rnk[cl]];
        return ;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tcnt[p]=std::min(tcnt[p*2],tcnt[p*2+1]);
    tsum[p]=tsum[p*2]+tsum[p*2+1];
}
void pushdown(int p,int cl,int cr){
    if(tag[p]!=0){
        tag[p*2]+=tag[p];
        tag[p*2+1]+=tag[p];
        tcnt[p*2]+=tag[p];
        tcnt[p*2+1]+=tag[p];
        tag[p]=0;
    }
}
void cntupdate(int p,int cl,int cr,int l,int r,int d){
    if(cl>=l&&cr<=r){
        tcnt[p]+=d;
        tag[p]+=d;
        return ;
    }
    if(cl!=cr){
        int mid=(cl+cr)/2;
        pushdown(p,cl,cr);
        if(mid>=l)cntupdate(p*2,cl,mid,l,r,d);
        if(mid<r)cntupdate(p*2+1,mid+1,cr,l,r,d);
        tcnt[p]=std::min(tcnt[p*2],tcnt[p*2+1]);
        if(tcnt[p*2]==tcnt[p*2+1]){
            tsum[p]=tsum[p*2]+tsum[p*2+1];
        }
        else{
            if(tcnt[p*2]>tcnt[p*2+1]){
                tsum[p]=tsum[p*2+1];
            }
            else{
                tsum[p]=tsum[p*2];
            }
        }
        return ;
    }
}
void aupdate(int p,int cl,int cr,int l,int d){
    if(cl==l&&cr==l){
        a[p]=d;
        tsum[p]=d;
        return ;
    }
    if(cl!=cr){
        int mid=(cl+cr)/2;
        pushdown(p,cl,cr);
        if(mid>=l)aupdate(p*2,cl,mid,l,d);
        if(mid<l)aupdate(p*2+1,mid+1,cr,l,d);
        if(tcnt[p*2]==tcnt[p*2+1]){
            tsum[p]=tsum[p*2]+tsum[p*2+1];
        }
        else{
            if(tcnt[p*2]>tcnt[p*2+1]){
                tsum[p]=tsum[p*2+1];
            }
            else{
                tsum[p]=tsum[p*2];
            }
        }
        return ;
    }
}
long long query(){
    return tsum[1];
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    dfs(1,0);
    build(1,1,n);
    int opt,x,y;
    for(int i{1};i<=q;i++){
        cin>>opt;
        if(opt==2){
            cin>>x;
            cntupdate(1,1,n,dfn[x],dfn[x]+siz[x]-1,(des[x])?-1:1);
            des[x]^=1;
        }
        if(opt==1){
            cin>>x>>y;
            aupdate(1,1,n,dfn[x],y);
        }
        cout<<query()<<"\n";
    }
    cout.flush();
    return 0;
}