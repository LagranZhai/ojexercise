#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6;
int a[maxn],k=0,n=0,ans1[maxn],ans2[maxn];
deque<int> q1,q2;
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=0;i<n;i++){
		cin>>a[i];
		while(!q1.empty()&&a[i]>a[q1.back()])q1.pop_back();
		while(!q1.empty()&&q1.front()<i-k+1)q1.pop_front();
		q1.push_back(i);
		ans1[i]=q1.front();
		while(!q2.empty()&&a[i]<a[q2.back()])q2.pop_back();
		while(!q2.empty()&&q2.front()<i-k+1)q2.pop_front();
		q2.push_back(i);
		ans2[i]=q2.front();
	}
	for(int i=k-1;i<n;i++){
		cout<<a[ans2[i]]<<" ";
	}
	cout<<"\n";
	for(int i=k-1;i<n;i++){
		cout<<a[ans1[i]]<<" ";
	}
	return 0;
}
