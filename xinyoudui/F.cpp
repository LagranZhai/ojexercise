//PF
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=1e6,maxm=1e6;
int n,m;
struct Edge{
    int v{0},nxt{0},w{0};
}edg[maxm*2];
int head[maxn*2],ecnt{0};
void addedge(int u,int v,int w){
    edg[++ecnt].v=v;
    edg[ecnt].w=w;
    edg[ecnt].nxt=head[u];
    head[u]=ecnt;
    return ;
}

int a[maxn+10];
int ch[maxn+10][2],fa[maxn+10],xorsum[maxn+10];
bool tag[maxn+10];
inline int chk(int x){
    if(ch[fa[x]][1]==x)return 1;
    if(ch[fa[x]][0]==x)return 0;
    return -1;
}
inline void upxorsum(int x){
    xorsum[x]=xorsum[ch[x][0]]^xorsum[ch[x][1]]^a[x];
}
inline void pushdown(int x){
    if(tag[x]){
        tag[ch[x][0]]^=1;
        std::swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
        tag[ch[x][1]]^=1;
        std::swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
        tag[x]=0;
    }
}
void reverse_pushdown(int x){
    if(chk(x)!=-1)reverse_pushdown(fa[x]);
    pushdown(x);
}
void spin(int x){
    int f=fa[x],dir=chk(x),ff=fa[f];
    if(chk(f)!=-1)ch[ff][chk(f)]=x;
    fa[ch[x][dir^1]]=f;ch[f][dir]=ch[x][dir^1];
    fa[f]=x;ch[x][dir^1]=f;fa[x]=ff;
    upxorsum(f);upxorsum(x);
}
void splay(int x){
    reverse_pushdown(x);
    int f=fa[x];
    while(chk(x)!=-1){
        if(chk(f)!=-1)spin(chk(f)==chk(x)?f:x);
        spin(x);
        f=fa[x];
    }
}
void access(int x){
    int son=0;
    while(x){
        splay(x);
        ch[x][1]=son;
        upxorsum(x);
        son=x;
        x=fa[x];
    }
}
void makeroot(int x){
    access(x);
    splay(x);
    tag[x]^=1;
    std::swap(ch[x][0],ch[x][1]);
}
int findroot(int x){
    // access(x);
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
void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
}
void cut(int x,int y){
    split(x,y);
    if(ch[y][0]==x&&fa[x]==y&&ch[x][1]==0){
        fa[x]=0;
        ch[y][0]=0;
        upxorsum(y);
    }
}
void link(int x,int y){
    makeroot(x);
    access(y);
    if(findroot(y)!=x)fa[x]=y;
}
std::vector<int> ans;
void dfs(int x){
    pushdown(x);
    if(ch[x][0])dfs(ch[x][0]);
    ans.push_back(x);
    if(ch[x][1])dfs(ch[x][1]);
}
bool check(int from,int to,int old){
    if(old==0){
        link(from,to);
        return false;
    }
    makeroot(n+1);
    access(from);
    if(findroot(to)==n+1){
        splay(to);
        ans.push_back(to);
        dfs(ch[to][1]);
        ans.push_back(to);
        return true;
    }
    else{
        cut(to,old);
        link(to,from);
        return false;
    }
}
std::queue<int > q;
bool inq[maxn*2];
int dis[maxn*2];
int cnt[maxn*2];
int nxt[maxn*2];
bool spfa(int n,int s){
    std::fill(dis,dis+maxn*2,std::numeric_limits<signed >::max()*2ll);
    std::fill(inq,inq+maxn*2,false);
    std::fill(cnt,cnt+maxn*2,0);
    q=std::queue<int >{};
    dis[s]=0;
    inq[s]=true;
    cnt[s]=1;
    q.push(s);
    while(!q.empty()){
        int cur{q.front()};
        q.pop();
        inq[cur]=0;
        for(int e{head[cur]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(dis[to]>dis[cur]+edg[e].w){
                dis[to]=dis[cur]+edg[e].w;
                cnt[to]=cnt[cur]+1;
                if(check(cur,to,nxt[to])){
                    return true;
                }
                nxt[to]=cur;
                if(cnt[to]>n)return true;
                if(!inq[to]){
                    q.push(to);
                    inq[to]=1;
                }
            }
        }
    }
    return false;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int a,b,c;
    for(int i{};i<m;i++){
        cin>>a>>b>>c;
        addedge(a,b,c);
    }
    for(int i{1};i<=n;i++){
        addedge(n+1,i,0);
    }
    if(spfa(n+1,n+1)){
        cout<<"YES ";
        for(int a:ans){
            cout<<a<<" ";
        }
    }
    else{
        cout<<"NO ";
    }
    cout<<"\n";
    cout.flush();
    return 0;
}