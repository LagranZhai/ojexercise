//P4172
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=5e3,maxm=3e5;
int n,m,q;
struct Edge{
    int u,v,w;
}edg[maxm];
int fa[maxm],ch[maxm][2];
using pii=std::pair<int,int>;
pii val[maxm]{{}},node[maxm];
bool tag[maxm];
void upval(int p){
    val[p]=std::max({node[p],val[ch[p][0]],val[ch[p][1]]});
}
int chk(int x){
    if(x==ch[fa[x]][0]){
        return 0;
    }
    else if(x==ch[fa[x]][1]){
        return 1;
    }
    else{
        return -1;
    }
}
void spin(int x){
    int dir{chk(x)},f{fa[x]},ff{fa[f]};
    if(chk(f)!=-1)ch[ff][chk(f)]=x;
    if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
    ch[f][dir]=ch[x][dir^1];
    fa[f]=x;ch[x][dir^1]=f;fa[x]=ff;
    upval(f);upval(x);
    return ;
}
void func(int x){
    if(x){
        tag[x]^=1;
        std::swap(ch[x][0],ch[x][1]);
    }
}
void pushdown(int x){
    if(tag[x]){
        func(ch[x][0]);
        func(ch[x][1]);
        tag[x]=0;
    }
}
void reverse_pushdown(int x){
    if(chk(x)!=-1)reverse_pushdown(fa[x]);
    pushdown(x);
}
void splay(int x,int rt=0){
    reverse_pushdown(x);
    int f=fa[x];
    while(chk(x)!=-1&&f!=rt){
        if(chk(f)!=-1&&fa[f]!=rt)spin(chk(f)==chk(x)?f:x);
        spin(x);
        f=fa[x];
    }
}
void access(int x){
    int son{0};
    while(x){
        splay(x);
        ch[x][1]=son;
        upval(x);
        son=x;
        x=fa[x];
    }
}
void makeroot(int x){
    access(x);
    splay(x);
    func(x);
}
int expose(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
    splay(x,y);
    pushdown(x);
    return ch[x][chk(x)^1];
}
void link(int x,int y){
    makeroot(y);
    fa[y]=x;
}
void linkedge(int x){
    link(edg[x].u,n+x);
    link(n+x,edg[x].v);
}
void cut(int x,int y){
    expose(x,y);
    if(ch[y][0]==x&&fa[x]==y&&ch[x][1]==0){
        fa[x]=0;
        ch[y][0]=0;
        upval(y);
    }
}
void cutedge(int x){
    cut(edg[x].u,x+n);
    cut(x+n,edg[x].v);
}
int findroot(int x){
    access(x);
    splay(x);
    int cur{x};
    pushdown(cur);
    while(ch[cur][0]){
        cur=ch[cur][0];
        pushdown(cur);
    }
    splay(cur);
    return cur;
}
bool checklink(int x,int y){
    makeroot(x);
    if(findroot(y)==x){
        return 1;
    }
    else{
        return 0;
    }
}
void addedge(int x){
    int cx{edg[x].u},cy{edg[x].v},cw{edg[x].w};
    if(checklink(cx,cy)){
        int ow=expose(cx,cy);
        if(val[ow].first<=cw){
            return ;
        }
        else{
            cutedge(val[ow].second-n);
            linkedge(x);
        }
    }
    else{
        linkedge(x);
    }
}
struct Op{
    int k,u,v;
};
std::stack<Op> s;
std::map<pii,int> e;
bool exist[maxm];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m>>q;
    for(int i{1};i<=n;i++){
        node[i]=val[i]={0,i};
    }
    for(int i{1};i<=m;i++){
        cin>>edg[i].u>>edg[i].v>>edg[i].w;
        e.insert({{edg[i].u,edg[i].v},i});
        exist[i]=1;
        val[n+i]=node[n+i]={edg[i].w,n+i};
    }
    int k,u,v;
    for(int i{1};i<=q;i++){
        cin>>k>>u>>v;
        s.push({k,u,v});
        if(k==2){
            if(e.find({u,v})==e.end()){
                std::swap(u,v);
            }
            exist[e[{u,v}]]=0;
        }
    }
    for(int i{1};i<=m;i++){
        if(exist[e[{edg[i].u,edg[i].v}]]){
            addedge(i);
        }
    }
    std::stack<int> ans;
    while(!s.empty()){
        Op cur{s.top()};
        if(cur.k==1){
            ans.push(val[expose(cur.u,cur.v)].first);
        }
        else{
            if(e.find({cur.u,cur.v})==e.end()){
                std::swap(cur.u,cur.v);
            }
            addedge(e[{cur.u,cur.v}]);
        }
        s.pop();
    }
    while(!ans.empty()){
        cout<<ans.top()<<"\n";
        ans.pop();
    }
    cout.flush();
    return 0;
}