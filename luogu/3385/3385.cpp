#include<iostream>
#include<queue>
using namespace std;
const int maxn=2e3+3;
const int maxm=3e3+3;
int T;
int n,m,cnt,head[maxn];
int inq[maxn];
struct Edge{
	int w,to,nxt;
}edg[maxm];
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		for(int i=1;i<=cnt;i++){
			edge[t].w=edge[t].to=edge[t].nxt=0;
		}
		for(int i=1;i<=n;i++)head[i]=0;
		n=m=cnt=0;
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			cin>>u>>v>>w;
			edg[++cnt].to=v;
			edg[cnt].w=w;
			edg[cnt].nxt=head[u];
			head[u]=cnt;
			if(w>=0){
				edg[++cnt].to=v;
				edg[cnt].w=w;
				edg[cnt].nxt=head[u];
				head[u]=cnt;
			}
		}
	}
	cout.flush();
	return 0;
}
