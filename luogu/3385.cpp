#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=2e3+3;
const int maxm=7e3+3;
int T;
int n,m,cnt,head[maxn],inq[maxn],dis[maxn];
int enq[maxn];
struct Edge{
	int w,to,nxt;
}edg[maxm];
bool spfa(int s){
	fill(dis+1,dis+n+1,0x3f7f3f7f);
	dis[s]=0;
	queue<int > q;
	q.push(s);
	inq[s]=1;
	enq[s]++;
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
					enq[edg[e].to]++;
					if(enq[edg[e].to]>=n)return false;
				}
			}
		}
	}
	return true; 
}
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		for(int i=1;i<=cnt+1;i++){
			edg[i].w=edg[i].to=edg[i].nxt=0;
		}
		for(int i=1;i<=n;i++){
			head[i]=0;enq[i]=0;dis[i]=0;inq[i]=0;
		}
		n=m=cnt=0;
		cin>>n>>m;
		int u,v,w;
		for(int i=1;i<=m;i++){
			cin>>u>>v>>w;
			edg[++cnt].to=v;
			edg[cnt].w=w;
			edg[cnt].nxt=head[u];
			head[u]=cnt;
			if(w>=0){
				edg[++cnt].to=u;
				edg[cnt].w=w;
				edg[cnt].nxt=head[v];
				head[v]=cnt;
			}
		}
		if(spfa(1))cout<<"NO"<<'\n';
		else cout<<"YES"<<'\n';
	}
	cout.flush();
	return 0;
}
