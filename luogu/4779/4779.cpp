#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
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
struct Cmp{
	bool operator()(Node &A,Node &B){
		return A.dis>B.dis;//greater<int>ÊÇÐ¡¸ù¶Ñ 
	}
};
priority_queue<Node,vector<Node>,Cmp> q;
void dij(int s){
	q.push(Node(s,0));
	while(!q.empty()){
		int cur=q.top().p;
		q.pop();
		if(visited[cur])continue;
		visited[cur]=1;
		for(int e=head[cur];e;e=edg[e].nxt){
			dis[edg[e].to]=min(dis[edg[e].to],dis[cur]+edg[e].w);
			if(!visited[edg[e].to])q.push(Node(edg[e].to,dis[edg[e].to]));
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
