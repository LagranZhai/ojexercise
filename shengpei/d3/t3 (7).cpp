#include<iostream>
#include<algorithm>
using namespace std;
const int M=998244353;
const int maxn=1e9+1;
//long long a[maxn+10],b[maxn+10],c[maxn+10];
void solve(){
//	a[1]=1;
//	for(int i=2;i<=maxn;i++){
//		a[i]=a[i-1]*i%M;
//	}
//	for(int i=1;i<=maxn;i++){
//		b[i]=b[i-1]+a[i];
//		b[i]%=M;
//	}
//	b[0]=1;
//	for(int i=2;i<=maxn;i++){
//		c[i]=c[i-1]+b[i-2];c[i]%=M;
//	}
//	b[0]=0;//?
//	a[1]=1;
	long long a=1,b=1,c=0,d=0,lb=1,llb=0;
	cout<<0<<',';
	int block=sqrt(maxn)*7;
	cout<<block<<endl;
	for(int i=2;i<=maxn;i++){
		a=a*i%M;llb=lb;lb=b;
		b=b+a;b%=M;		
		c=c+llb;c%=M;
		d=a-(((1+(2*lb)%M-c))%M)+M+i-2;d%=M;
		if(i%block==0){
			cout<<d<<',';
		}
	}
	
}
//int a[100]={0,0,
//0,
//2,
//12,
//70,
//464,
//3498,
//29572,
//277406,
//2863800,
//32303314};
int main(){
	freopen("table.txt","w",stdout);
	ios::sync_with_stdio(false);
	int t;
	solve();
	
	return 0;
}
