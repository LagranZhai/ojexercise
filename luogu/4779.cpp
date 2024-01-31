#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=1e5,maxm=2e5;
#define int long long
int n,m,s;
struct Edge{
	int v,nxt,w;
}edg[maxm*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v,int w){
	edg[++cnt]={v,head[u],w};
	head[u]=cnt;
}
int dis[maxn*2];
bool vis[maxn*2];
struct Node{
	int v,dis;
};
void dijkstra(int s){
	std::fill(dis,dis+maxn*2,std::numeric_limits<int>::max()>>2);
	auto cmp{[](const Node &a,const Node &b){return a.dis>b.dis;}};
	std::priority_queue<Node,std::vector<Node> ,decltype(cmp)> q(cmp);
	dis[s]=0;
	q.push({s,0});
	while(!q.empty()){
		int cur{q.top().v};
		q.pop();
		if(vis[cur])continue;
		vis[cur]=1;
		for(int e{head[cur]};e;e=edg[e].nxt){
			int to{edg[e].v};
			if(!vis[to]&&dis[to]>dis[cur]+edg[e].w){
				dis[to]=dis[cur]+edg[e].w;
				q.push({to,dis[to]});
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m>>s;
	int u,v,w;
	for(int i{1};i<=m;i++){
		cin>>u>>v>>w;
		addedge(u,v,w);
	}
	dijkstra(s);
	for(int i{1};i<=n;i++){
		cout<<dis[i]<<" ";
	}
	cout.flush();
	return 0;
}