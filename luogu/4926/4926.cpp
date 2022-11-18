#include<iomanip>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=2e3;
const int maxm=2e3;
const double eps=1e-6;
int n,m,t,cnt=0,score[maxn],times[maxn],head[maxn];
bool inq[maxn];
double dis[maxn];
struct Edge{
	int to,nxt;
	//long long w;
	double k;
	bool o;
}edg[maxm];
bool spfa(double t){
	fill(dis,dis+maxn,1);
	fill(inq,inq+maxn,0);
	fill(times,times+maxn,0);
	queue<int > q;
	for(int i=1;i<=n;i++){
		inq[i]=1;dis[i]=1;times[i]++;q.push(i);
	}
	while(!q.empty()){
		int cur=q.front();
		q.pop();
		inq[cur]=0;
		for(int e=head[cur];e;e=edg[e].nxt){
			int vv=edg[e].to;
			if(edg[e].o){
				if(dis[vv]-dis[cur]*(edg[e].k-t)<eps){
					dis[vv]=dis[cur]*(edg[e].k-t);
					if(!inq[vv]){
						inq[vv]=1;
						q.push(vv);
						if(++times[vv]>=n)return true;
					}
				}
			}
			else{
				if(dis[vv]-dis[cur]*1.0/(edg[e].k+t)<eps){
					dis[vv]=dis[cur]*1.0/(edg[e].k+t);
					if(!inq[vv]){
						inq[vv]=1;
						q.push(vv);
						if(++times[vv]>=n)return true;
					}
				}
			}
		}
	}
	return false;
}
int main(){
	ios::sync_with_stdio(false);
	int s;
	cin>>n>>m>>s;
	int opt;
	int u,v,kk;
	int mk=-1;
	for(int i=1;i<=m;i++){
		cin>>opt>>u>>v>>kk;
		mk=max(mk,kk);
		edg[++cnt].to=v;
		edg[cnt].k=kk;
		edg[cnt].nxt=head[u];
		head[u]=cnt;
		if(opt==1){
			edg[cnt].o=1;
		}
		else{
			edg[cnt].o=0;
		}
	}
	int C,x;
	for(int i=1;i<=s;i++){
		cin>>C>>x;
		score[C]=x;
	}
//	for(int i=1;i<=n;i++){
//		edg[++cnt].w=1;
//		edg[cnt].to=i;
//		edg[cnt].nxt=head[n+1];
//		head[n+1]=cnt;
//	}
	double l=0.0,r=mk,mid=(l+r)/2.0;
	while(l+eps>r){
		mid=(l+r)/2.0;
		if(!spfa(mid)){
			l=mid;
		}
		else{
			r=mid;
		}
	}
	cout<<fixed<<setprecision(8)<<mid;
	return 0;
}
