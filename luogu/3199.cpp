#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=3e3,maxm=1e4;
constexpr double eps=1e-9;
#define int long long
struct Edge{
	int v,nxt;
	double w;
}edg[maxm*3];
int head[maxn*2],cnt{0};
int n,m;
void addedge(int u,int v,double w){
	edg[++cnt]={v,head[u],w};
	head[u]=cnt;
}
//int in[maxn*2],s;
double minw{std::numeric_limits<double>::max()},maxw{std::numeric_limits<double>::lowest()};
double dis[maxn*2];
bool inq[maxn*2];
int times[maxn*2];
bool vis[maxn*2];
bool spfa(int s,double del){
	std::fill(dis,dis+maxn*2,std::numeric_limits<double>::max());
	std::fill(inq,inq+maxn*2,0);
	std::fill(times,times+maxn*2,0);
	dis[s]=0;inq[s]=1;
	std::queue<int> q;
	q.push(s);
	while(!q.empty()){
		int cur{q.front()};
		q.pop();
		inq[cur]=0;
		for(int e{head[cur]};e;e=edg[e].nxt){
			int to{edg[e].v};
            if(vis[to])continue;
			// vis[to]=1;
			double w{edg[e].w-del};
			if(dis[to]>dis[cur]+w){
				dis[to]=dis[cur]+w;
				times[to]=times[cur]+1;
				if(times[to]>=n){//n=100 run fast and ac, but how?
					return true;
				}
				if(!inq[to]){
					q.push(to);
					inq[to]=1;
				}
			}
		}
	}
    q.push(s);vis[s]=1;
    while(!q.empty()){
        int cur{q.front()};
        q.pop();
        for(int e{head[cur]};e;e=edg[e].nxt){
            int to{edg[e].v};
            if(!vis[to]){
                vis[to]=1;
                q.push(to);
            }
        }
    }
	return false;
}
bool check(double del){
	std::fill(vis,vis+maxn*2,0);
	for(int i{1};i<=n;i++){
		if(!vis[i]){
			if(spfa(i,del))return 1;
		}
	}
	return 0;
}
signed main(){
//	freopen("3199.in","r",stdin);
	ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n>>m;
	int u,v;
	double w;
	for(int i{1};i<=m;i++){
		cin>>u>>v>>w;
		maxw=std::max(maxw,w);
		minw=std::min(minw,w);
		addedge(u,v,w);
//		in[v]++;
	}
//	for(int i{1};i<=n;i++){
//		if(in[i]==0){
//			s=i;
//			break;
//		}
//	}
	double l=minw,r=maxw,mid=(minw+maxw)/2.0,ans;
	while(r-l>=eps){
		mid=(l+r)/2.0;
		if(check(mid)){//negative circle exists
			r=mid;
		}
		else{
			ans=mid;
			l=mid;
		}
	}
	cout<<std::fixed<<std::setprecision(8)<<ans<<"\n";
	cout.flush();
	return 0;
} 