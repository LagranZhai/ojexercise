#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+5;
long long dp[maxn];
int f[maxn],n,siz[maxn],tag[maxn];
vector<int> tree[maxn];
int dfs(int p){
	if(tag[p]==1)return -1;
	tag[p]=1;
	for(int i=0;i<tree[i].size();i++){
		if(dfs(tree)!=-1)siz[i]+=siz[a];		
	}
	siz[p]+=1;
	tag[p]=0;
	return 0;
}
int solve(int i){
	if(tag[i]==1)return -1;
	tag[i]=1;
	int hua=0,num=0;
	for(int i=0;i<tree[i].size();i++){
		if(dfs(a)!=-1)hua+=hua[];		
	}
	siz[i]+=1;
	tag[i]=0;
	return 0;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>f[i];
	}
	int a,b;
	for(int i=1;i<n;i++){
		cin>>a>>b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	
	return 0;
}
