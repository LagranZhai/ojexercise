//P2173
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=1e4*2,maxm=1e5*2,maxc=10;
int n,m,c,k;
int a[maxn];
struct Lct{
    int fa[maxn],ch[maxn][2],val[maxn];
    bool tag[maxn];
    int chk(int x){
        if(x==ch[fa[x]][0])return 0;
        if(x==ch[fa[x]][1])return 1;
        return -1;
    }
    void upval(int x){
        val[x]=std::max({a[x],val[ch[x][0]],val[ch[x][1]]});
    }
    void func(int x){
        if(x){
            std::swap(ch[x][0],ch[x][1]);
            tag[x]^=1;
        }
    }
    void pushdown(int x){
        if(x&&tag[x]){
            func(ch[x][0]);
            func(ch[x][1]);
            tag[x]=0;
        }
    }
    void reverse_pushdown(int x){
        if(chk(x)!=-1)reverse_pushdown(fa[x]);
        pushdown(x);
    }
    void spin(int x){
        int f{fa[x]},dir{chk(x)},ff{fa[f]};
        if(dir==-1)return ;
        if(chk(f)!=-1)ch[ff][chk(f)]=x;
        if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
        ch[f][dir]=ch[x][dir^1];ch[x][dir^1]=f;
        fa[f]=x;fa[x]=ff;
        upval(f);upval(x);
        return ;
    }
    void splay(int x,int des=0){
        reverse_pushdown(x);
        int f{fa[x]};
        while(chk(x)!=-1&&f!=des){
            if(chk(f)!=-1&&fa[f]!=des)spin(chk(f)==chk(x)?f:x);
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
            return true;
        }
        else{
            return false;
        }
    }
    void link(int x,int y){
        if(!checklink(x,y)){
            makeroot(x);
            fa[x]=y;
        }
    }
    void update(int x){//:P
        splay(x);
    }
    void cut(int x,int y){
        makeroot(x);
        access(y);
        splay(y);
        if(fa[x]==y&&ch[y][0]==x&&ch[x][1]==0){
            fa[x]=0;
            ch[y][0]=0;
            upval(y);
        }
    }
    int getmax(int x,int y){
        makeroot(x);
        access(y);
        splay(y);
        return val[y];
    }
}tree[maxc+2];
using pii=std::pair<int,int>;
std::map<pii,int> cofedge;
int getc(int u,int v){
    if(cofedge.find({u,v})==cofedge.end()){
        std::swap(u,v);
    }
    if(cofedge.find({u,v})==cofedge.end()){
        return -1;
    }
    else{
        return cofedge[{u,v}];
    }
}
int deg[maxn][maxc+2];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m>>c>>k;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    int u,v,w;
    for(int i{1};i<=m;i++){
        cin>>u>>v>>w;
        tree[w].link(u,v);
        cofedge[{u,v}]=w;
        deg[u][w]++;deg[v][w]++;
    }
    int opt;
    for(int i{1};i<=k;i++){
        cin>>opt;
        if(opt==0){
            cin>>u>>v;
            a[u]=v;
            for(int i{0};i<c;i++){
                tree[i].update(u);
            }
        }
        else if(opt==1){
            cin>>u>>v>>w;
            int cc{getc(u,v)};
            if(cc!=w){
                if(cc==-1){
                    cout<<"No such edge.\n";
                    continue;
                }
                if(deg[u][w]>=2||deg[v][w]>=2){
                    cout<<"Error 1.\n";
                    continue;
                }
                if(tree[w].checklink(u,v)){
                    cout<<"Error 2.\n";
                    continue;
                }
                deg[u][cc]--;deg[v][cc]--;
                deg[u][w]++;deg[v][w]++;
                if(cofedge.find({u,v})==cofedge.end()){
                    std::swap(u,v);
                }
                cofedge[{u,v}]=w;
                tree[cc].cut(u,v);
                tree[w].link(u,v);
            }
            cout<<"Success.\n";
        }
        else if(opt==2){
            cin>>w>>u>>v;
            if(!tree[w].checklink(u,v)){
                cout<<"-1\n";
            }
            else{
                cout<<tree[w].getmax(u,v)<<"\n";
            }
        }
    }
    cout.flush();
    return 0;
}