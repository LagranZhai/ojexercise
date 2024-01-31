#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=5e3;
#define int long long
struct Edge{
	int v,nxt,w;
}edg[maxn*5];
int head[maxn*2],cnt{0};
void addedge(int u,int v,int w){
	edg[++cnt]={v,head[u],w};
	head[u]=cnt;
}
int n,m;
int dis[maxn*2];
bool inq[maxn*2];
int times[maxn*2];
bool spfa(int s){
	std::fill(dis,dis+maxn*2,std::numeric_limits<int>::max()>>2);
	dis[s]=0;inq[s]=1;
	std::queue<int> q;
	q.push(s);
	while(!q.empty()){
		int cur{q.front()};
		q.pop();
		inq[cur]=0;
		for(int e{head[cur]};e;e=edg[e].nxt){
			int to{edg[e].v};
			if(dis[to]>dis[cur]+edg[e].w){
				dis[to]=dis[cur]+edg[e].w;
				times[to]=times[cur]+1;
				if(times[to]>n){
					return 1;
					break;
				}
				if(!inq[to]){
					q.push(to);
					inq[to]=1;
				}
			}
		}
	}
	return 0;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m;
	int u,v,w;
	for(int i{1};i<=m;i++){
		cin>>u>>v>>w;
		addedge(v,u,w);
	}
	for(int i{1};i<=n;i++){
		addedge(n+1,i,0);
	}
	if(spfa(n+1)){
		cout<<"NO\n";
	}
	else{
		for(int i{1};i<=n;i++){
			cout<<dis[i]<<" ";
		}
	}
	cout.flush();
	return 0;
}