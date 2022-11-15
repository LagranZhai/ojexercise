#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=5100;
const int maxm=4e5+100;
int cnt=0,n,m,fa[maxn];
struct Edge{
	int u,v,w;
}edg[maxm];
int findx(int x){
	return fa[x]==x?x:fa[x]=findx(fa[x]);
}
int kruskal(){
	sort(edg+1,edg+m+1,[](const Edge &A,const Edge &B){
		return A.w<B.w;
	});
	int cur=1,ans=0,num=0;
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
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	//int u,v,w;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>edg[i].u>>edg[i].v>>edg[i].w;
	}
	int k=kruskal();
	if(k<0)cout<<"orz\n";
	else cout<<k<<'\n';
	return 0;
} 
