//5357ac 
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=2e5+5;
int ch[maxn][27];
bool cnt[maxn];
string s,t;
int fail[maxn],num[maxn],jump[maxn],in[maxn],tag[maxn];
int tot=0;
void ins(string &s,int o){
	int p=0;
	for(auto c:s){
		if(!ch[p][c-'a'])ch[p][c-'a']=++tot;
		p=ch[p][c-'a'];
	}
	cnt[p]=1;
	jump[o]=p;
}
void acam(){
	int p=0;
	queue<int> q;
	for(int i=0;i<26;i++){
		if(ch[0][i])q.push(ch[0][i]);
	}
	while(!q.empty()){
		p=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(ch[p][i]){
				fail[ch[p][i]]=ch[fail[p]][i];
				in[ch[fail[p]][i]]++;
				q.push(ch[p][i]);
			}
			else ch[p][i]=ch[fail[p]][i];
		}
	}
}
void query(string &s){
	int p=0;
	for(auto c:s){
		p=ch[p][c-'a'];
		int q=p; 
		if(cnt[q]){
			++num[q];
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	//freopen("P3796_3.in","r",stdin);
	int n=0;	
		cin>>n;
		for(int i=0;i<n;i++){
		 	cin>>s;
			ins(s,i);
			//cout<<i<<endl;
		}
		acam();
		cin>>t;
		query(t);
		for(int i=1;i<=tot;i++){
//			if(!in[i]){
				int p=i,temp=num[p];
//				tag[fail[p]]+=num[p];
//				p=fail[p];
				while(fail[p]){
					num[fail[p]]+=temp;
					p=fail[p];
				}
//			}
		}
		for(int i=0;i<n;i++){
			cout<<num[jump[i]]<<"\n";
		}
	return 0;
}
