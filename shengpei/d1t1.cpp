#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;
using pii=pair<int,int>;
const int maxp=31623;
vector<int > p;
vector<int > q;
vector<int > now;
void fenjie(int x){
	for(int i=2;i*i<=x;i++){
		if(x==1)break;
		int cnt=0;
		while(x%i==0){
			cnt++;
			x/=p[i];
		}
		if(cnt>0){
			p.push_back(i);
			q.push_back(cnt);
		}
	}
	if(x>1){
		p.push_back(x);
		q.push_back(1);
	}
}
int print2(int d){
	if(d==q.size()){
		int x=1;
		now.push_back(1);
		for(int i=1;i<=q[q.size()-1];i++){
			x*=p;
			now.push_back(x);
		}
		return now.size();
	}
	int ss=print2(d+1);
	int x=1;
	for(int i=1;i<=a[d].second;i++){
		x*=p[d];
		if(i%2==0){
			for(int j=0;j<ss;j++){
				now.push_back(x*now[j]);
			}
		}
		else{
			for(int j=ss-1;j>=0;j--){
				now.push_back(x*now[j]);
			}
		}
	}
	return now.size();
}
void print1(){
	for(int i=1;i<=a)
}
void print(){
	cout<<1<<' ';
    int ss=print2(2);
	for(int i=0;i<=q[0];i++){
		
	}
}
int main(){
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	int n;	
	while(T--){
		cin>>n;
		p.clear();
		fenjie(n);	
		for(int i=0;i<q.size())
	}
	return 0;
}
