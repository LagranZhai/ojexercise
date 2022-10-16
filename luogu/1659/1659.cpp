#include<iostream>
#include<cstdio>
#include<string>
#include<queue>
using namespace std;
const int maxn=1e6+10;
const int p=19930726;
int n,d[maxn],m;
long long k,ans=1;
long long cnt[maxn];
//priority_queue<int> q; 
string s;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'||c<='9')x=x*10+(c-'0'),c=getchar();
	return x*f;
}
void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
void manacher(string &s){
	int mid=0,r=0;
	for(int i=0;i<s.size();i++){
		if(i<r)d[i]=min(d[2*mid-i],r-i);
		while(i-d[i]-1>=0&&i+d[i]+1<s.size()&&s[i-d[i]-1]==s[i+d[i]+1])d[i]++;
		if(i+d[i]>r)mid=i,r=i+d[i];
		m=m<2*d[i]+1?2*d[i]+1:m;
		cnt[2*d[i]+1]++;
	}
}
long long fastpow(int i,long long t){
	long long a=1,b=i;
	while(t>0){
		if(t|0)a=a*b%p;
		t>>=1;
		b=b*b%p;
	}
	return a;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k>>s;
	manacher(s);
	long long t=0;
	for(int i=m;i>0;i--){
		t+=cnt[i];
		if(k>t){
			ans=(ans*fastpow(i,t))%p;
			k-=t;
		}
		else{
			ans=(ans*fastpow(i,k))%p;
			break;
		}
	}
	cout<<ans<<endl;
	return 0;
}

