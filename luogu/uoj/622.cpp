#include<iostream>
#include<algorithm>
#include<queue>
#include<limits>
using namespace std;
using ll=long long;
constexpr int maxn=3e5+5,maxm=1e6+5;
int n,m,s,cnt=0,head[maxn];
ll dis[maxn];
bool visited[maxn];
struct Edge{
	int to,nxt;
    ll w;
}edg[maxm];
priority_queue<pair<ll,int >,vector<pair<ll,int > >,greater<pair<ll,int > > > q;
void dij(int s){
	fill(dis+1,dis+n+1,std::numeric_limits<ll>::max());
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){
		int cur=q.top().second;
		q.pop();
		if(visited[cur])continue;
		visited[cur]=1;
        if(dis[cur]==std::numeric_limits<ll>::max())continue;
		for(int e=head[cur];e;e=edg[e].nxt){
			dis[edg[e].to]=min(dis[edg[e].to],dis[cur]+edg[e].w);
			if(!visited[edg[e].to])q.push(make_pair(dis[edg[e].to],edg[e].to));
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>s;
	int u,v;
    ll w;
	for(int i=0;i<m;i++){
		cin>>u>>v>>w;
		edg[++cnt].to=v;
		edg[cnt].w=w;
		edg[cnt].nxt=head[u];
		head[u]=cnt;
	}
	dij(s);
	for(int i=1;i<=n;i++){
		cout<<((dis[i]<std::numeric_limits<ll>::max())?dis[i]:-1)<<' ';
	}
	return 0;
} 