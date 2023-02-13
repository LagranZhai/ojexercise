#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;
int n,fail[maxn];
string s;
void getfail(string &s,int m){
	fail[0]=-1;
	for(int i=1;i<m;i++){
		int j=fail[i-1];
		while(j>=0&&s[j+1]!=s[i])j=fail[j];
		if(s[j+1]==s[i])j++;
		fail[i]=j;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>s;
	getfail(s,n);
	cout<<n-fail[n-1]-1<<endl;
	return 0;
}
