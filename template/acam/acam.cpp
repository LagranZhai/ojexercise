//3808ac 
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1e6+6;
int ch[100][27],cnt[100];
string s,t;
int fail[100];
int tot=0,ans=0;
void ins(string &s){
	int p=0;
	for(auto c:s){
		if(!ch[p][c-'a'])ch[p][c-'a']=++tot;
		p=ch[p][c-'a'];
	}
	cnt[p]++;
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
		if(cnt[p]>0){
			ans+=cnt[p];
			cnt[p]=-1;
		}	
	}
}
int main(){
	ios::sync_with_stdio(false);
	int n=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		ins(s);
		//cout<<i<<endl;
	}
	acam();
	cin>>t;
	query(t);
	cout<<ans<<endl;
	return 0;
}
