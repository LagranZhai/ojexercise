#include<bits/stdc++.h>
using namespace std;
const int maxn=10005;
struct Flight{
	int s,e;
}m1[10006],m2[10006];
int nm1[maxn],nm2[maxn];
int main(){
	ios::sync_with_stdio(false);
	int n,mm1,mm2;
	cin>>n>>mm1>>mm2;
	//cout<<n<<mm1<<mm2;
	for(int i=0;i<mm1;i++){
		cin>>m1[i].s;
		cin>>m1[i].e;
	}
	for(int i=0;i<mm2;i++){
		cin>>m2[i].s;
		cin>>m2[i].e;
	}
	//cout<<"a"<<endl;
	sort(m1,m1+mm1,[](const Flight& mm11,const Flight& mm12)->bool{return mm11.s<mm12.s;});
	sort(m2,m2+mm2,[](const Flight& mm21,const Flight& mm22)->bool{return mm21.s<mm22.s;});
	//cout<<"a"<<endl;
	priority_queue< int,vector< int >,greater< int > > e1,e2; 
	for(int i=0;i<mm1;i++){
		cout<<i<<endl;
		while(!e1.empty()&&e1.top()<=m1[i].s)e1.pop();
		e1.push(m1[i].e);
		for(int j=e1.size();j<=n;j++){
			nm1[j]++;
		}
	}
	//cout<<"a"<<endl;
	int mn1[maxn]={};
	for(int i=0;i<mm2;i++){
		while(!e2.empty()&&e2.top()<=m2[i].s)e2.pop();
		e2.push(m2[i].e);
		mn1[i]=e2.size();
		for(int j=e2.size();j<=n;j++){
			nm2[j]++;
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		ans=(ans<nm1[i]+nm2[n-i])?(nm1[i]+nm2[n-i]):ans;
	}
	cout<<ans;
	return 0;
}
