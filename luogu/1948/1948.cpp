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
	fill_n(dp[0],dp[0]+(maxn*maxn),0x3f7f3f7f);
	dp[1][0]=0;
	inq[1][0]=1;
	queue<pair<int,int>> q;
	q.push(make_pair(1,0));
	while(!q.empty()){
		pair<int,int> cur=q.front();
		q.pop();
		inq[cur.first][cur.second]=0;
		for(int e=head[cur.first];e;e=edg[e].nxt){
			int vv=edg[e].to;
			if(cur.second+1<=k){
				if(dp[vv][cur.second+1]>dp[cur.first][cur.second]){
					dp[vv][cur.second+1]=dp[cur.first][cur.second];
					if(!inq[vv][cur.second+1]){
						q.push(make_pair(vv,cur.second+1));
						inq[vv][cur.second]=1;
					}
				}
			}
			if(max(dp[cur.first][cur.second],edg[e].w)<dp[vv][cur.second]){
				dp[vv][cur.second]=max(dp[cur.first][cur.second],edg[e].w);
				if(!inq[vv][cur.second]){
					q.push(make_pair(vv,cur.second));
					inq[vv][cur.second]=1;
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
	}
	spfa();
	cout<<dp[n][k]<<'\n';
	return 0;
} 
