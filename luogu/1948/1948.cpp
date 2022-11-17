#include<iostream>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;
const int maxn=1e3+10;
const int maxm=1e4+100;
int n,m,k,head[maxn],cnt=0;
struct Edge{
	int to,nxt,w;
}edg[maxm];
int inq[maxn][maxn],dp[maxn][maxn];
bool spfa(){
	fill(dp[0],dp[0]+(maxn*maxn),0x3f7f3f7f);
	for(int i=0;i<=n;i++){
		dp[1][i]=0;
	}
	inq[1][0]=1;
	queue<pair<int,int>> q;
	q.push(make_pair(1,0));
	while(!q.empty()){
		pair<int,int> cur=q.front();
		q.pop();
		int nn=cur.first,ck=cur.second;
		inq[nn][ck]=0;
		for(int e=head[nn];e;e=edg[e].nxt){
			int vv=edg[e].to;
			if(ck+1<=k){
				if(dp[vv][ck+1]>dp[nn][ck]){
					dp[vv][ck+1]=dp[nn][ck];
					if(!inq[vv][ck+1]){
						q.push(make_pair(vv,ck+1));
						inq[vv][ck+1]=1;
					}
				}
			}
			if(max(dp[nn][ck],edg[e].w)<dp[vv][ck]){
				dp[vv][ck]=max(dp[nn][ck],edg[e].w);
				if(!inq[vv][ck]){
					q.push(make_pair(vv,ck));
					inq[vv][ck]=1;
				}
			}
		}
	}
	return true;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	int u,v,w;
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		edg[++cnt].w=w;
		edg[cnt].to=v;
		edg[cnt].nxt=head[u];
		head[u]=cnt;
		edg[++cnt].w=w;
		edg[cnt].to=u;
		edg[cnt].nxt=head[v];
		head[v]=cnt;
	}
	spfa();
	int ans=dp[n][k];
	for(int i=0;i<=k;i++)ans=min(ans,dp[n][i]);
	if(dp[n][k]==0x3f7f3f7f)cout<<-1<<'\n';
	else cout<<ans<<'\n';
	return 0;
} 
