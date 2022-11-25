#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+100;
const int maxm=5e5+100;
int cnt=0,n,m,fa[maxn];
int f[maxn][2];
struct Edge{
	int u,v,w;
}edg[maxm];
int findx(int x){
	return fa[x]==x?x:fa[x]=findx(fa[x]);
}
__int128 kruskal(){
	sort(edg+1,edg+m+1,[](const Edge &A,const Edge &B){
		return A.w<B.w;
	});
	fill(f[0],f[0]+maxn*2,0x3f7f3f7f);
	int cur=1,num=0;
	__int128 ans=0;
	while(cur<=m){
		if(edg[cur].w<f[edg[cur].u][1]){
			if(edg[cur].w<f[edg[cur].u][0]){
				f[edg[cur].u][1]=f[edg[cur].u][0];
				f[edg[cur].u][0]=edg[cur].w;
			}
			else{
				f[edg[cur].u][1]=edg[cur].w;
			}			
		}
		if(edg[cur].w<f[edg[cur].v][1]){
			if(edg[cur].w<f[edg[cur].v][0]){
				f[edg[cur].v][1]=f[edg[cur].v][0];
				f[edg[cur].v][0]=edg[cur].w;
			}
			else{
				f[edg[cur].v][1]=edg[cur].w;
			}
		}
		cur++;
	}
	cur=1;
	while(cur<=m){
		if(findx(edg[cur].u)!=findx(edg[cur].v)){
			ans+=edg[cur].w;
			fa[fa[edg[cur].u]]=fa[edg[cur].v];
			++num;
			if(num==n-1)return ans;
		}
		cur++;
	}
	return -1;
}
void write(__int128 x){
	if(x<(__int128)0)putchar('-'),x=-x;
	if(x>(__int128)9)write(x/(__int128)10);
	putchar(x%(__int128)10+'0');
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	//int u,v,w;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>edg[i].u>>edg[i].v>>edg[i].w;
	}
	//__int128 k=kruskal();
	int k=kruskal();
	//__int128 ans=0;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(f[i][1]==0x3f7f3f7f){
			ans-=1;
		}
		else{
			ans+=k-f[i][0]+f[i][1];
		}
	}
	write(ans);
	return 0;
} 
