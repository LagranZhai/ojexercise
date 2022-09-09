#include<string.h>
#include<iostream>
using namespace std;
const int maxn=2e7+7;
string a,b;
const string c="$";
long long z[maxn*2];
void zal(string a){
	z[0]=a.size();
	int l=0,r=0;
	for(int i=1;i<a.size();++i){
		//if(i%100==1)cout<<i<<endl;
		//int s=0;
		if(i<r){
			if(z[i-l]<r-i+1){
				z[i]=z[i-l];
			}
			else z[i]=r-i+1;
		}
		//if(l+z[l]>i) z[i]=min(z[i-l],l+z[l]-i);
		while(i+z[i]<a.size()&&a[z[i]]==a[z[i]+i]){
			//if(i!=1)cout<<i<<endl;
			z[i]++;
		}
		//if(i+z[i]>l+z[l]) l=i;
		if(i+z[i]-1>r)l=i,r=i+z[i]-1;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	freopen("P5410_2.in","r",stdin);	
	//int ans1,ans2;
	cin>>a>>b;
	long long lb=b.size();
	b+=c;
	b+=a;
	zal(b);
	long long ans1=lb+1ll;
	for(int i=1;i<lb;i++){		
		ans1^=1ll*(i+1)*(z[i]+1);
	}
	//cout<<b<<endl;
	//cout<<lb<<endl;
	long long ans2=z[lb+1]+1;
	//cout<<z2[lb+1]<<"\n";
	for(int i=lb+2;i<lb+a.size()+1;i++){
		//cout<<z2[i]<<"\n";
		ans2^=1ll*(i-lb)*(z[i]+1);
	}
	cout<<ans1<<"\n"<<ans2;
	fclose(stdin);
	return 0;
}
