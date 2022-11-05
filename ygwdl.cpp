#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+6;
int n,m,cnt=0;
int fa[maxn];
vector<int> edge[maxn];
template<typename T>
T fr(){
	T w=0,f=1;
	char c=cin.get();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=cin.get();
	}
	while(c>='0'&&c<='9')w=w*10+c-'0',c=cin.get();
	return w*f;
}
void bfs(int i,int f,int c){
	fa[i]=c;
	//ch[c]++;
	for(int j:edge[i]){
		if(j==f)continue;
		bfs(j,i,c);
	}
	return;
}
void isbct(int i){
	if(fa[i])return;
	++cnt;
	bfs(i,i,cnt);
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	int a,b;
	for(int i=0;i<m;i++){
		a=fr<int>();
		b=fr<int>();
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	//bool flag=1;
	//int num=0;
	for(int i=1;i<=n;i++){
		isbct(i);
	}
	cout<<cnt-1<<endl;
	return 0;
}
