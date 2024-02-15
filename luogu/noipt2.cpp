#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=4e5;
const int maxm=4e5+100;
int n,m,fa[maxn];
struct Edge{
	int u,v,w;
}edge[maxm];
struct Edg{
    int v,nxt,w;
}edg[maxm*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v,int w){
    edg[++cnt]={v,head[u],w};
    head[u]=cnt;
}
constexpr int P=1e9+7;
int qpow(int a,int b){
    int c{1};
    while(b){
        if(b&1)c=c*a%P;
        b>>=1;
        a=a*a%P;
    }
    return c;
}
int findx(int x){
	return fa[x]=(fa[x]==x)?x:findx(fa[x]);
}
void kruskal(){
	int cur=1,num=0;
    std::vector<int> ans{};
	while(cur<=m){
		if(findx(edge[cur].u)!=findx(edge[cur].v)){
			addedge(edge[cur].u,edge[cur].v,qpow(2,edge[cur].w));
            addedge(edge[cur].v,edge[cur].u,qpow(2,edge[cur].w));
			fa[fa[edge[cur].u]]=fa[edge[cur].v];
			++num;
			if(num==n-1)return ;
		}
		cur++;
	}
	return ;
}

int siz[maxn*2];
void dfs1(int x,int f){
    siz[x]=1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs1(to,x);
            siz[x]+=siz[to];
        }
    }
}
void dfs2(int x,int f,int &ans){
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs2(to,x,ans);
            ans=(ans+edg[e].w*siz[to]%P*(n-siz[to])%P)%P;
        }
    }
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	//int u,v,w;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>edge[i].u>>edge[i].v;
        edge[i].w=i;
	}
    kruskal();
    int ans{0};
    dfs1(1,0);
    dfs2(1,0,ans);
    cout<<ans<<"\n";
	return 0;
} 