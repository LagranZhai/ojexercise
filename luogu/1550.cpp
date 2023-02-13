#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=310;
const int maxm=9e4+500;
int n,m=0,fa[maxn];
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
			if(num==n)return ans;
		}
		cur++;
	}
	return -1;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	//int u,v,w;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		++m;
		edg[m].u=n+1;
		edg[m].v=i;
		cin>>edg[m].w;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			m++;
			edg[m].u=i;
			edg[m].v=j;
			cin>>edg[m].w;
		}
	}
	int k=kruskal();
	if(k<0)cout<<"orz\n";
	else cout<<k<<'\n';
	return 0;
} 
