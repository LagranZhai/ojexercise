//3808ac 
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=2e4;
int ch[100][27];
bool cnt[maxn];
string s,t,mp[maxn];
int fail[maxn],num[maxn];
int tot=0;
int maxans;
vector<string> ans;
void ins(string &s,int o){
	int p=0;
	for(auto c:s){
		if(!ch[p][c-'a'])ch[p][c-'a']=++tot;
		p=ch[p][c-'a'];
	}
	cnt[p]=1;
	mp[p]=to_string(o)+s;
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
		while(p){
			if(cnt[p]){
				++num[p];
				if(num[p]>maxans){
					ans.clear();
					maxans=num[p];
					ans.push_back(mp[p]);
				}
				else if(num[p]==maxans)ans.push_back(mp[p]);	
			}
			p=fail[p];
		}	
	}
}
int main(){
	ios::sync_with_stdio(false);
	freopen("P3796_1.in","r",stdin);
	int n=0;	
	while(1){
		cin>>n;
		if(!n)break;
		memset(ch,0,sizeof ch);
		memset(fail,0,sizeof fail);
		memset(cnt,0,sizeof cnt);
		memset(num,0,sizeof num);
		tot=maxans=0;
		ans.clear();
		for(int i=0;i<maxn;i++){
			mp[i].clear();
		}
		for(int i=0;i<n;i++){
		 	cin>>s;
			ins(s,i);
		//cout<<i<<endl;
		}
		acam();
		cin>>t;
		query(t);
		cout<<maxans<<endl;
		sort(ans.begin(),ans.end());
		for(string a:ans){
			int i=0;
			while(a[i]>='0'&&a[i]<='9')i++;
			cout<<a.substr(i,a.size()-i)<<endl;
		}
	}
	return 0;
}
