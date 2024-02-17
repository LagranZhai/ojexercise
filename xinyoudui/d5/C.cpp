//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=500,maxm=1e6;
int n;
int cnt=0,fa[maxn];
struct Edge{
	int u,v,w;
}edg[maxm];

int findx(int x){
	return fa[x]=(fa[x]==x)?x:findx(fa[x]);
}
std::pair<int,int> kruskal(){
	std::sort(edg+1,edg+cnt+1,[](const Edge &A,const Edge &B){
		return A.w<B.w;
	});
    for(int i{1};i<=n+1;i++)fa[i]=i;
	int cur=1,ans=0,num=0,line{0};
	while(cur<=cnt){
		if(findx(edg[cur].u)!=findx(edg[cur].v)){
			ans+=edg[cur].w;
			fa[fa[edg[cur].u]]=fa[edg[cur].v];
			++num;
            if(edg[cur].w!=0)line++;
			if(num==n)return {line,ans};
		}
		cur++;
	}
	return {-1,-1};
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n;
    int w;
    for(int i{1};i<=n;i++){
        cin>>w;
        edg[++cnt]={i,n+1,w};
        edg[++cnt]={n+1,i,w};
    }
    for(int i{1};i<=n;i++){
        for(int j{1};j<=n;j++){
            cin>>w;
            if(i!=j){
                edg[++cnt]={i,j,w};
                // edg[++cnt]={j,i,w};
            }
        }
    }
    auto ans{kruskal()};
    cout<<ans.second<<"\n";
    cout.flush();
    return 0;
}