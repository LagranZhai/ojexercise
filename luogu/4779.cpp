#include<bits/stdc++.h>
using std::cin;using std::cout;using std::cerr;
#define int long long
constexpr int maxn=3e5;
int n,m,s;
struct Edge{
	int v,nxt,w;
}edg[maxn*2];
int head[maxn],cnt{0};
void addedge(int u,int v,int w){
	edg[++cnt]={v,head[u],w};
	head[u]=cnt;
}
bool vis[maxn];
int dis[maxn];
void dijkstra(int s){
	std::fill(dis,dis+maxn,std::numeric_limits<int>::max()>>2);
	dis[s]=0;
	using pii=std::pair<int,int>;
	auto cmp=[](const pii& A,const pii &B){return A.second>B.second;};
	std::priority_queue<pii,std::vector<pii> ,decltype(cmp)> q(cmp);
	q.push({s,0});
	while(!q.empty()){
		int cur{q.top().first};q.pop();
		if(!vis[cur]){
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
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m>>s;
	int u,v,w;
	for(int i{};i<m;i++){
		cin>>u>>v>>w;
		addedge(u,v,w);
	}
	dijkstra(s);
	for(int i{1};i<=n;i++){
		cout<<dis[i]<<" ";
	}
	cout<<"\n";
	cout.flush();
	return 0;
}