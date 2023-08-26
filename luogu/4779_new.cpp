#include<iostream>
#include<algorithm>
#include<queue>
#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using namespace std;
const int maxn=1e5+5;
const int maxm=2e5+5;
int n,m,s,cnt=0,dis[maxn],head[maxn];
bool visited[maxn];
struct Edge{
	int to,w,nxt;
}edg[maxm];
typedef pair<int, int > PII;
__gnu_pbds::priority_queue<PII,greater<PII >,thin_heap_tag > q;
__gnu_pbds::priority_queue<node, myCmp, pairing_heap_tag>::point_iterator its[N];

//priority_queue<pair<int,int >,vector<pair<int,int > >,greater<pair<int,int > > > q;
void dij(int s){
	q.push(make_pair(0,s));
	while(!q.empty()){
		int cur=q.top().second;
		q.pop();
		if(visited[cur])continue;
		visited[cur]=1;
		for(int e=head[cur];e;e=edg[e].nxt){
			dis[edg[e].to]=min(dis[edg[e].to],dis[cur]+edg[e].w);
			if(!visited[edg[e].to])q.push(make_pair(dis[edg[e].to],edg[e].to));
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>s;
	int u,v,w;
	for(int i=0;i<m;i++){
		cin>>u>>v>>w;
		edg[++cnt].to=v;
		edg[cnt].w=w;
		edg[cnt].nxt=head[u];
		head[u]=cnt;
	}
	fill(dis+1,dis+n+1,0x3f7f3f7f);
	dis[s]=0;
	dij(s);
	for(int i=1;i<=n;i++){
		cout<<dis[i]<<' ';
	}
	return 0;
} 
