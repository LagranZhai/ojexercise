#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+1000;
int lg[8]={1,10,100,1000,10000,100000,1000000,10000000};
bitset<maxn> bs;
int ans[maxn],cnt=0,sna[maxn];
int j[maxn];
inline bool isnana(int x){
	int flag=0;
	while(x>0){
		if(x%10==7){flag=1;break;
		}
		x/=10;
	}
	return flag;
}
void init(){
	for(int i=1;i<=maxn;i++){
		if(bs[i])continue;
		if(isnana(i)){
			for(int t=i;t<maxn;t+=i){	
				bs[t]=1;
			}
		}
		else{
			ans[++cnt]=i;
			sna[i]=cnt;
		}
	}
}
int main(){
	freopen("P7960_2.in","r",stdin);
	ios::sync_with_stdio(false);
	//int t=0;
	init();
	//cout<<'a'<<endl;
	int T,a;
	cin>>T;
	while(T--){
		cin>>a;
		if(bs[a])cout<<-1<<'\n';
		else{
			cout<<ans[sna[a]+1]<<'\n';
		}
	}
	//cout<<bs[1003]; 
	cout.flush();
	//fclose(stdin);
	return 0;
}
