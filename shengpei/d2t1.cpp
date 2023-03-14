#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
using pii=pair<string,int>;
vector<pii> res;
string s;
const char ab[28]={'0','a','b','c','d','e','f','g','h','i','j','k',
'l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
void biaoshi(int p){
	int a[28]={0},cnt=0;string bs;
	for(int i=p;i<s.size();i++){
		if(a[s[i]-'a']==0){
			a[s[i]-'a']=++cnt;
		}
		bs+=ab[a[s[i]-'a']];
	}
	res.push_back(make_pair(bs,p+1));
}
int main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;	
	cin>>s;
	for(int i=0;i<s.size();i++){
		biaoshi(i);
	}
	sort(res.begin(),res.end());
	for(auto i:res){
		cout<<i.second<<' ';
	}
	cout.flush();
	return 0;
}
