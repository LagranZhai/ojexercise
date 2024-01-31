#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define N 200003
#define reg register
#define ll long long
#define ls son[u][0]
#define rs son[u][1]
#define mid ((l+r)>>1)
using namespace std;

struct edge{
    int u,v,w;
    inline edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
}ed[N];

int a[N],st[N];
vector<int> adj[N*3];
int n,m;

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

struct Link_Cut_Tree{ //板子,没什么好说的
    int rev[N],pos[N],fa[N],son[N][2];

    inline void pushup(int u){
        pos[u] = u;
        if(ls&&a[pos[ls]]>a[pos[u]]) pos[u] = pos[ls];
        if(rs&&a[pos[rs]]>a[pos[u]]) pos[u] = pos[rs];
    }   

    inline void pushr(int u){
        swap(ls,rs);
        rev[u] ^= 1;
    }

    inline void pushdown(int u){
        if(!rev[u]) return;
        if(ls) pushr(ls);
        if(rs) pushr(rs);
        rev[u] = 0;
    }

    inline bool notrt(int u){
        return son[fa[u]][0]==u||son[fa[u]][1]==u;
    }

    inline void rotate(int x){
        int y = fa[x],z = fa[y];
        int k = son[y][1]==x,w = son[x][k^1];
        if(notrt(y)) son[z][son[z][1]==y] = x;
        son[x][k^1] = y;
        son[y][k] = w;
        if(w) fa[w] = y;
        fa[y] = x,fa[x] = z;
        pushup(y);
    }

    inline void splay(int x){
        reg int y = x,z = 0;
        st[++z] = y;
        while(notrt(y)) st[++z] = y = fa[y];
        while(z) pushdown(st[z--]);
        while(notrt(x)){
            y = fa[x],z = fa[y];
            if(notrt(y))
                rotate((son[z][1]==y)==(son[y][1]==x)?y:x);
            rotate(x);  
        }
        pushup(x);
    }

    inline void access(int u){
        for(reg int v=0;u;u=fa[u]){
            splay(u),rs = v;
            pushup(u),v = u;
        }
    }

    inline void makeroot(int u){
        access(u),splay(u);
        pushr(u);
    }

    inline void split(int u,int v){
        makeroot(u);
        access(v),splay(v);
    }

    inline void link(int u,int v){
        makeroot(u);
        fa[u] = v;
    }

    inline void cut(int u,int v){
        split(u,v);
        son[v][0] = fa[u] = 0;
        pushup(v);
    }

    inline int query(int u,int v){
        split(u,v);
        return pos[v];
    }

    inline int findroot(int u){
        access(u),splay(u);
        pushdown(u);
        while(ls){
            u = ls;
            pushdown(u);
        }
        splay(u);
        return u;
    }

    inline bool linked(int u,int v){
        makeroot(u);
        return findroot(v)==u;
    }
}T;

const int lim = 32766;
int s1[N],s2[N]; //这是两个栈,记录边和它的状态 删除/添加
int top,cnt;
ll ans = 1; //答案要 +1

void insert(int nl,int nr,int l,int r,int u,int k){
    if(nl<=l&&r<=nr){ //加入一条边,注意这个线段树不用也不能下传标记
        adj[u].push_back(k);
        return; 
    }
    if(nl<=mid) insert(nl,nr,l,mid,u<<1,k);
    if(nr>mid) insert(nl,nr,mid+1,r,u<<1|1,k);
}

void solve(int l,int r,int x){
    int d,u,v,w,j,lst = top,ln = adj[x].size();
    for(reg int i=0;i<ln;++i){
        j = adj[x][i];
        u = ed[j].u,v = ed[j].v;
        w = ed[j].w;
        if(T.linked(u,v)){
            d = T.query(u,v)-n;
            if(ed[d].w<=w) continue; //当前边权比路径上最大的还大,就不用加进去
            ans -= ed[d].w;
            T.cut(ed[d].u,d+n),T.cut(ed[d].v,d+n); 
			s1[++top] = d; 
			s2[top] = -1;
        } 
        T.link(u,n+j),T.link(n+j,v);
        s1[++top] = j;
        s2[top] = 1;
        ans += w;
    }
    if(l==r) printf("%lld\n",ans);
	else{
		solve(l,mid,x<<1);
		solve(mid+1,r,x<<1|1);
	}
	while(top>lst){ //回溯
		d = s1[top];
		u = ed[d].u,v = ed[d].v;
		w = ed[d].w;
		if(s2[top]==-1){
			T.link(u,d+n),T.link(v,d+n);
			ans += w;
		}else{
			T.cut(u,d+n),T.cut(v,d+n);
			ans -= w;
		}
		--top;
	}
}
	
int main(){
    freopen("4319.in","r",stdin);
    freopen("4319.out","w",stdout);
    int l,r,u,v,w;
    read(n);
    for(reg int i=1;i<n;++i){
        read(u),read(v),read(w);
        ed[++cnt] = edge(u,v,w);
        a[n+cnt] = w;
        insert(1,lim,1,lim,1,cnt);
    }
    cerr<<"b";
    read(m);
    for(reg int i=1;i<=m;++i){
        read(u),read(v),read(w),read(l),read(r);
        ed[++cnt] = edge(u,v,w);
        a[n+cnt] = w;
        insert(l,r,1,lim,1,cnt);
    }
    cerr<<"a";
    solve(1,lim,1);
    return 0;
}