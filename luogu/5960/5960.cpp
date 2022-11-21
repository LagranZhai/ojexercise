#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=5e3+100;
const int maxm=1e4+100;
int n,m,cnt=0,head[maxn],dis[maxn],inq[maxn],times[maxn];
struct Edge{
	int to,w,nxt;
}edg[maxm];
bool spfa(int s){
	fill(dis,dis+maxn,0x3f7f3f7f);
	dis[s]=0;
	inq[s]=1;
	times[s]=1; 
	queue<int > q;
	q.push(s);
	while(!q.empty()){
		int cur=q.front();
		q.pop();
		inq[cur]=0;
		for(int e=head[cur];e;e=edg[e].nxt){
			int vv=edg[e].to;
			if(dis[vv]>dis[cur]+edg[e].w){
				dis[vv]=dis[cur]+edg[e].w;
				if(!inq[vv]){
					q.push(vv);
					inq[vv]=1;
					if(++times[vv]>=n+1)return false;
				}
			}
		}
	}
	return true;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	int u,v,w;
	for(int i=1;i<=m;i++){
		cin>>v>>u>>w;
		edg[++cnt].w=w;
		edg[cnt].to=v;
		edg[cnt].nxt=head[u];
		head[u]=cnt;
	}
	for(int i=1;i<=n;i++){
		edg[++cnt].w=0;
		edg[cnt].to=i;
		edg[cnt].nxt=head[n+1];
		head[n+1]=cnt;
	}
	if(spfa(n+1)){
		for(int i=1;i<=n;i++)cout<<dis[i]<<' ';
	}
	else cout<<"NO";
	cout.flush();
	return 0;
}
