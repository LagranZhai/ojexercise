//5357ac 
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
char stack[maxn];
int top=0,n=0;
int ch[maxn][27];
bool cnt[maxn];
string s,t[maxn];
int fail[maxn],num[maxn],jump[maxn],in[maxn];
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
		++num[p];
	}
}
void topu(){
	queue<int> q;
	for(int i=1;i<=tot;i++){
		if(!in[i])q.push(i);
	}
	while(!q.empty()){
		int p=q.front();q.pop();
		num[fail[p]]+=num[p];
		in[fail[p]]--;
		if(!in[fail[p]])q.push(fail[p]);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>s;
	for(auto c:s){
		if(c=='B'&&top!=0){
			top--;
			continue;
		}
		if(c=='P'){
			string te(stack,top+1);
			t[++n]=te;
			ins(te,n);
			continue;
		}
		stack[++top]=c;
	}
	acam();
	int m=0;	
	cin>>m;
	int a=0,b=0;
	for(int i=0;i<m;i++){
	 	cin>>a>>b;
	 	query(t[b]);
	 	topu();
	 	
	}

		for(int i=0;i<n;i++){
			cout<<num[jump[i]]<<"\n";
		}
	return 0;
}
