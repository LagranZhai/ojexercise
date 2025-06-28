//P3385
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=1e4;
int T;
int n,m;
struct Edge{
	int v,nxt,w;
}edg[maxn*3];
int head[maxn],cnt{0};
void addedge(int u,int v,int w){
	edg[++cnt]={v,head[u],w};
	head[u]=cnt;
}
int inq[maxn];
int dis[maxn];
int len[maxn];
bool spfa(int s,int n){
	std::fill(dis,dis+maxn,std::numeric_limits<int>::max()>>2);
	std::fill(len,len+maxn,0);
	// std::fill(inq,inq+maxn,0);
	dis[s]=0;inq[s]=T+1;len[s]=1;
	std::queue<int> q;
	q.push(s);
	while(!q.empty()){
		int cur{q.front()};q.pop();
		inq[cur]=0;
		for(int e{head[cur]};e;e=edg[e].nxt){
			int to{edg[e].v};
			if(dis[to]>dis[cur]+edg[e].w){
				len[to]=len[cur]+1;
				dis[to]=dis[cur]+edg[e].w;
				if(len[to]>=n+1)return true;
				if(inq[to]!=T+1){
					q.push(to);
					inq[to]=T+1;
				}
			}
		}
	}
	return false;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n>>m;
		int u,v,w;
		for(int i{1};i<=m;i++){
			cin>>u>>v>>w;
			if(w>=0)addedge(v,u,w);
			addedge(u,v,w);
		}
		if(spfa(1,n)){
			cout<<"YES\n";
		}
		else{
			cout<<"NO\n";
		}
		std::fill(head,head+n+1,0);
		std::fill(edg,edg+cnt+1,Edge{});
		cnt=0;
	}
	cout.flush();
	return 0;
}