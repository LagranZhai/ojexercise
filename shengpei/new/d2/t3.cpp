#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=5e5;
#define int long long
int fa[maxn],oldfa[maxn],tag[maxn],sum[maxn],ch[maxn][2],unrealt[maxn],a[maxn];
void upsum(int x){
    sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+unrealt[x]+a[x];
    return ;
}
void pushdown(int x){
    if(tag[x]){
        tag[ch[x][0]]^=1;
        tag[ch[x][1]]^=1;
        std::swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
        std::swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
        tag[x]=0;
    }
}
int chk(int x){
    if(x==ch[fa[x]][0])return 0;
    if(x==ch[fa[x]][1])return 1;
    return -1;
}
void reverse(int x){
    if(chk(x)!=-1)reverse(fa[x]);
    // std::cerr<<"a"<<x<<"b";
    pushdown(x);
}
void spin(int x){
    int f=fa[x],ff=fa[f],dir=chk(x);
    if(chk(f)!=-1)ch[ff][chk(f)]=x;
    fa[x]=ff;
    fa[ch[x][dir^1]]=f;ch[f][dir]=ch[x][dir^1];
    fa[f]=x;ch[x][dir^1]=f;
    upsum(f);upsum(x);
}
void splay(int x){
    reverse(x);
    int f=fa[x];
    while(chk(x)!=-1){
        if(chk(f)!=-1)spin(chk(f)==chk(x)?f:x);
        spin(x);
        f=fa[x];
    }
    return ;
}
void access(int x){
    int son=0;
    splay(x);
    if(fa[x]==0){
        return ;
    }
    while(x){
        splay(x);
        unrealt[x]+=sum[ch[x][1]];
        unrealt[x]-=sum[son];
        ch[x][1]=son;
        int olds=sum[x];
        upsum(x);
        if(sum[x]!=olds)std::cerr<<"wrong";
        son=x;
        x=fa[x];
        // std::cerr<<x;
    }
}
void makeroot(int x){
    access(x);
    splay(x);
    // std::cerr<<890;
    std::swap(ch[x][0],ch[x][1]);
    tag[x]^=1;
    upsum(x);
}
int findroot(int x){
    access(x);
    splay(x);
    int cur=x;
    while(x){
        pushdown(x);
        cur=x;
        x=ch[x][0];
    }
    splay(cur);
    return cur;
}
void link(int x,int y){
    makeroot(x);
    findroot(y);
    if(findroot(y)!=x){
        fa[x]=y;
        unrealt[y]+=sum[x];
        upsum(y);
    }
}
void cut(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
    if(ch[y][0]==x){
        fa[x]=0;
        ch[y][0]=0;
        upsum(y);
    }
    else{
        fa[x]=0;
        ch[y][1]=0;
        upsum(y);
    }
}
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
void dfs(int x,int f){
    oldfa[x]=f;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x);
        }
    }
}
struct Edg{
    int u,v;
}edgs[maxn*3];
int ecnt=0;
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        edgs[++ecnt].u=u;
        edgs[ecnt].v=v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    dfs(1,0);
    upsum(1);
    // for(int i{1};i<n;i++){
    //     link(edgs[i].u,edgs[i].v);
    //     // std::cerr<<fa[2]<<" "<<fa[3]<<"\n";
    // }
    for(int i{2};i<=n;i++){
        link(i,oldfa[i]);
    }
    int opt,x,y;
    // makeroot(1);
    // cout<<sum[1]<<"\n";
    for(int i{1};i<=q;i++){
        cin>>opt;
        if(opt==1){
            cin>>x>>y;
            makeroot(x);
            a[x]=y;
            upsum(x);
            // std::cerr<<fa[2]<<" "<<fa[3]<<"\n";
        }
        if(opt==2){
            cin>>x;
            // cout<<"old"<<oldfa[x]<<"\n";
            if(des[x]){
                // access(2);splay(2);
                // splay(1);
                // cout<<sum[1]<<" "<<sum[2]<<"\n";
                link(x,oldfa[x]);
                des[x]^=1;
            }
            else{
                cut(oldfa[x],x);
                des[x]^=1;
            }
        }
        // std::cerr<<"que";
        makeroot(1);
        cout<<sum[1]<<"\n";
    }
    return 0;
}