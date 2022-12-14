//3796ac 
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=2e4;
int ch[maxn][27];
bool cnt[maxn];
string s,t,mp[maxn];
int fail[maxn],num[maxn],ord[maxn];
int tot=0;
int maxans;
vector<int> ans;
void ins(string &s,int o){
	int p=0;
	for(auto c:s){
		if(!ch[p][c-'a'])ch[p][c-'a']=++tot;
		p=ch[p][c-'a'];
	}
	cnt[p]=1;
	mp[p]=s;
	ord[p]=o;
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
		int q=p; 
		while(q){
			if(cnt[q]){
				++num[q];
				if(num[q]>maxans){
					ans.clear();
					maxans=num[q];
					ans.push_back(q);
				}
				else if(num[q]==maxans)ans.push_back(q);	
			}
			q=fail[q];
		}	
	}
}
int main(){
	ios::sync_with_stdio(false);
	freopen("P3796_3.in","r",stdin);
	int n=0;	
	while(1){
		cin>>n;
		if(!n)break;
		memset(ch,0,sizeof ch);
		memset(fail,0,sizeof fail);
		memset(cnt,0,sizeof cnt);
		memset(num,0,sizeof num);
		tot=0,maxans=0;
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
		sort(ans.begin(),ans.end(),[](const int &p,const int &q)->bool{
			return ord[p]<ord[q];
		});
		for(int a:ans){
			cout<<mp[a]<<endl;
		}
	}
	return 0;
}
