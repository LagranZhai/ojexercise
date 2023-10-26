#include<iostream>
#include<algorithm>
#include<queue>
#include<limits>
#include<bits/extc++.h>
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;
using std::cin,std::ios,std::max,std::min;
const int maxn=1e5+5;
const int maxm=2e5+5;
int n,m,s,cnt=0,dis[maxn],head[maxn];
bool visited[maxn];
struct Edge{
	int to,w,nxt;
}edg[maxm];
struct Node{
	int p,dis;
	Node(int _p,int _dis):p(_p),dis(_dis){}
};
typedef std::pair<int, int> PII;
__gnu_pbds::priority_queue<PII,std::greater<PII>,__gnu_pbds::thin_heap_tag> q;
__gnu_pbds::priority_queue<PII,std::greater<PII>,__gnu_pbds::thin_heap_tag>::point_iterator its[maxn+10];
//priority_queue<pair<int,int >,vector<pair<int,int > >,greater<pair<int,int > > > q;
void dij(int s){
	std::fill(dis+1,dis+n+1,0x3f7f3f7f);
	dis[s]=0;
	its[s]=q.push(std::make_pair(0,s));
	while(!q.empty()){
		int cur=q.top().second;
		q.pop();
		if(visited[cur])continue;
		visited[cur]=1;
		for(int e=head[cur];e;e=edg[e].nxt){
			dis[edg[e].to]=min(dis[edg[e].to],dis[cur]+edg[e].w);
			if(!visited[edg[e].to]){
				if(its[edg[e].to]!=nullptr){
					q.modify(its[edg[e].to],std::make_pair(dis[edg[e].to],edg[e].to));
				}
				else its[edg[e].to]=q.push(std::make_pair(dis[edg[e].to],edg[e].to));
			}
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
	dij(s);
	for(int i=1;i<=n;i++){
		std::cout<<dis[i]<<' ';
	}
	return 0;
} 
