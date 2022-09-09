//3805ac
#include<cstring>
#include<iostream>
using namespace std;
const int maxn=11e6+6;
string a;
int p[maxn];
int ans=0;
void manacherj(string &a){
	int mid=0,r=0;
	for(int i=0;i<a.size();i++){
		if(i<r)p[i]=min(p[(mid<<1)-i],r-i);
		while(i-p[i]-1>=0&&i+p[i]+1<a.size()&&a[i-p[i]-1]==a[i+p[i]+1])p[i]++;
		if(i+p[i]>r)mid=i,r=i+p[i];
		ans=max(ans,p[i]*2+1);
	}
}
void manachero(string &a){
	int mid=0,r=0;
	for(int i=1;i<a.size();i++){
		if(i<=r)p[i]=min(p[(mid<<1)-i-1],r-i+1);
		while(i-p[i]-1>=0&&i+p[i]<a.size()&&a[i-p[i]-1]==a[i+p[i]])p[i]++;
		if(i+p[i]-1>r)mid=i,r=i+p[i]-1;
		ans=max(ans,p[i]*2);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>a;
	manacherj(a);
	manachero(a);
	cout<<ans<<endl;
	return 0;
}
