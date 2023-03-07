#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4;
const int maxm=4e5;
int head[maxn*2],cnt=0;
int dis[maxn*2],vis[maxn*2]; 
int n,m,b,nmax=-1,f[maxn*2];
struct Edge{
	int to,nxt,w;
}edge[maxm*2];
void addedge(int _u,int _v,int _w){
	edge[++cnt].nxt=head[_u];
	edge[cnt].w=_w;
	edge[cnt].to=_v;
	head[_u]=cnt;
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>b;
	for(int i=1;i<=n;i++){
		cin>>f[i];
		nmax=f[i]>nmax?f[i]:nmax;
	}
	int u,v,w;
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		addedge(u,v,w);
		addedge(v,u,w);
	}
	
	cout.flush();
	return 0;
} 
