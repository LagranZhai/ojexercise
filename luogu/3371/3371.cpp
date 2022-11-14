#include<iostream>
#include<queue>
using namespace std;
const int maxm=5e5+5;
const int maxn=2e4;
int head[maxn],cnt;
int n,m,s;
long long dis[maxn];
bool inq[maxn];
struct Edge{
	int to,nxt;
	long long w;
}edg[maxm];
void spfa(int s){
	queue<int> q;
	q.push(s);
	inq[s]=1;
	while(!q.empty()){
		int cur=q.front();
		q.pop();
		inq[cur]=0;
		for(int e=head[cur];e;e=edg[e].nxt){
			if(dis[edg[e].to]>dis[cur]+edg[e].w){
				dis[edg[e].to]=dis[cur]+edg[e].w;
				if(!inq[edg[e].to]){
					q.push(edg[e].to);
					inq[edg[e].to]=1;
				}
			}
		}
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	int u,v,w;
	cin>>n>>m>>s;
	for(int i=1;i<=m;++i){
		cin>>u>>v>>w;
		edg[++cnt].w=w;
		edg[cnt].to=v;
		edg[cnt].nxt=head[u];
		head[u]=cnt;
	}
	long long t=(1ll<<31)-1;
	fill(dis+1,dis+n+1,t);
	dis[s]=0;
	spfa(s);
	for(int i=1;i<=n;++i){
		cout<<dis[i]<<" ";
	}
	return 0;
}
