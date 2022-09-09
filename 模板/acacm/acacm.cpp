#include<iostream>
#include<cstring>
#incldue<queue>
using namespace std;
const int maxn=1e6+6;
int ch[maxn][27];
string s,t;
int fail[maxn][27];
int tot=0;
void ins(string &s){
	int p=0;
	for(auto c:s){
		if(!ch[p][c-'a'])ch[p][c-'a']=++tot;
		p=ch[p][c-'a'];
	}
	cnt[p]++;
}
void acmac(){
	int p=0,fail[p]=0;
	queue<int> q;
	
	for(int i=0;i<26;i++){
		
	}
}
int main(){
	ios::sync_with_stdio(false);
	int n=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		//ins(s);
	}
	acmac();
	cin>>t;
	findt(t);
	return 0;
}
