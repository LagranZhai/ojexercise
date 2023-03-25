#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;
int n,fail[maxn];
string s,t;
void getfail(string &s){
	int m=s.size();
	fail[0]=-1;
	int j=-1;
	for(int i=1;i<m;i++){
		while(j>=0&&s[j+1]!=s[i])j=fail[j];
		if(s[j+1]==s[i])j++;
		fail[i]=j;
	}
}
void kmp(string &s,string &t){
	int m=s.size();
	int n=t.size();
	int j=-1;
	for(int i=0;i<n;i++){
		while(j>=0&&s[j+1]!=t[i])j=fail[j];
		if(s[j+1]==t[i])j++;
		if(j==m-1)cout<<i-m+2<<'\n';
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>t>>s;
	getfail(s);
	kmp(s,t);
	for(int i=0;i<s.size();i++){
		cout<<fail[i]+1<<' ';
	}
	cout.flush();
	return 0;
}
