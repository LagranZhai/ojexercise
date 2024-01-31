//P4319
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
// #define int long long
constexpr int maxn=5e4+10,maxm=32766*3;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(long long x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10ll);
	putchar(x%10ll+'0');
	return;
}
int n,m;
struct Edge{
    int u,v,w;
}edg[maxn+maxm+10];
int ecnt{0};
std::vector<int> tree[maxm*4];
void update(int p,int cl,int cr,int l,int r,const int& v){
    if(cl>=l&&cr<=r){
        tree[p].push_back(v);
        return ;
    }
    if(cl!=cr){
        int mid{(cl+cr)/2};
        if(l<=mid)update(p*2,cl,mid,l,r,v);
        if(r>mid)update(p*2+1,mid+1,cr,l,r,v);
    }
}
int fa[maxn*2+maxm],ch[maxn*2+maxm][2];
using pii=std::pair<int,int>;
pii val[maxn*2+maxm]{{}},node[maxn*2+maxm];
bool tag[maxn*2+maxm];
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
    pushdown(y);
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
long long sum{0};
struct op{
    long long opt,x;
    void func(){
        if(opt==1){
            sum=x;
        }
        else if(opt==2){
            linkedge(x);
        }
        else{
            cutedge(x);
        }
    }
};
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
void addedge(int x,std::stack<op>& s){
    int cx{edg[x].u},cy{edg[x].v},cw{edg[x].w};
    // if(1){
        int ow=expose(cx,cy);
        if(val[ow].first<=cw){
            return ;
        }
        else{
            s.push({1,sum});
            sum-=val[ow].first;sum+=cw;
            s.push({2,val[ow].second-n});
            cutedge(val[ow].second-n);
            s.push({3,x});
            linkedge(x);
        }
    // }
    // else{
    //     s.push({3,x});
    //     linkedge(x);
    //     s.push({1,sum});
    //     sum+=cw;
    // }
}
void dfs(int p,int cl,int cr){
    std::stack<op> s;
    for(auto a:tree[p]){
        addedge(a,s);
    }
    if(cl==cr){
        // cout<<sum+1<<"\n";
        write(sum+1);
        putchar('\n');
    }
    else{
        int mid{(cl+cr)/2};
        dfs(p*2,cl,mid);
        dfs(p*2+1,mid+1,cr);
    }
    while(!s.empty()){
        op cur{s.top()};
        cur.func();
        s.pop();
    }
    return ;
}
signed main(){
    // ios::sync_with_stdio(false);cin.tie(nullptr);
    // freopen("4319.in","r",stdin);
    // freopen("4319.out","w",stdout);
    // cin>>n;
    n=read();
    int u,v,w;
    for(int i{1};i<=n;i++){
        node[i]=val[i]={0,i};
    }
    for(int i{1};i<n;i++){
        // cin>>u>>v>>w;
        u=read();v=read();w=read();
        sum+=w;
        edg[++ecnt]={u,v,w};
        val[n+ecnt]=node[n+ecnt]={w,n+ecnt};
        linkedge(ecnt);
    }
    // cerr<<"b";
    cin>>m;
    int l,r;
    for(int i{1};i<=m;i++){
        // cin>>u>>v>>w>>l>>r;
        u=read();v=read();w=read();l=read();r=read();
        edg[++ecnt]={u,v,w};
        val[n+ecnt]=node[n+ecnt]={w,n+ecnt};
        update(1,1,32766,l,r,ecnt);
    }
    // cerr<<"a";
    dfs(1,1,32766);
    cout.flush();
    return 0;
}