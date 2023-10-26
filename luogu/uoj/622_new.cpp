#include<iostream>
#include<algorithm>
#include<queue>
#include<limits>
#include<bits/extc++.h>
using std::cin,std::ios,std::max,std::min;
using ll=long long;
constexpr int maxn=3e5+5,maxm=1e6+5;
int n,m,s,cnt=0,head[maxm],vcnt=0,deg[maxm],nxtv[maxm];
ll dis[maxm];
bool visited[maxm];
struct Edge{
	int to,nxt;
    ll w;
}edg[maxm*2];
void addedge(int u,int v,ll w){

	edg[++cnt].to=v;
	edg[cnt].w=w;
	edg[cnt].nxt=head[u];
	head[u]=cnt;
}
int constdegree(int u){
	if(deg[nxtv[u]]>m/n){
		addedge(nxtv[u],++vcnt,0);
		nxtv[u]=cnt;
	}
	deg[nxtv[u]]++;
	return nxtv[u];
}
typedef std::pair<ll, int> PLI;
__gnu_pbds::priority_queue<PLI,std::greater<PLI>,__gnu_pbds::thin_heap_tag> q;
__gnu_pbds::priority_queue<PLI,std::greater<PLI>,__gnu_pbds::thin_heap_tag>::point_iterator its[maxn+10];
//priority_queue<pair<ll,int >,vector<pair<ll,int > >,greater<pair<ll,int > > > q;
void dij(int s){
	std::fill(dis+1,dis+vcnt+1,std::numeric_limits<ll>::max());
	std::fill(dis+1,dis+vcnt+1,std::numeric_limits<ll>::max());
	dis[s]=0;
	its[s]=q.push(std::make_pair(0,s));
	q.push(std::make_pair(0,s));
	// for(int i{1};i<=n;i++){
	// 	its[i]=q.push(std::make_pair(std::numeric_limits<ll>::max(),i));
	// }
	q.modify(its[s],std::make_pair(0,s));
	while(!q.empty()){
		int cur=q.top().second;
		q.pop();
		if(visited[cur])continue;
		visited[cur]=1;
        if(dis[cur]==std::numeric_limits<ll>::max())continue;
		for(int e=head[cur];e;e=edg[e].nxt){
			dis[edg[e].to]=min(dis[edg[e].to],dis[cur]+edg[e].w);
			if(!visited[edg[e].to])q.modify(its[edg[e].to],std::make_pair(dis[edg[e].to],edg[e].to));	
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>s;
	vcnt=n;
	for(int i{1};i<=n;i++)nxtv[i]=i;
	int u,v;
    ll w;
	for(int i=0;i<m;i++){
		cin>>u>>v>>w;
		addedge(constdegree(u),constdegree(v),w);
	}
	dij(s);
	for(int i=1;i<=n;i++){
		std::cout<<((dis[i]<std::numeric_limits<ll>::max())?dis[i]:-1)<<' ';
	}
	return 0;
} 