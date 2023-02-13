#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
const long long M=1073741824ll;
int n,q,a[maxn];
void sol(int l,int r){
	if(l-r>=63){
		cout<<"Too large"<<"\n";
		return;
	}
	if(l==r){
		if(a[l]>M)cout<<"Too large"<<"\n";
		else cout<<max(1,a[l])<<"\n";
		return;
	}
	long long ansl=1ll,tagl,ansr=1ll,tagr,ansm=1ll;
	for(tagl=l;tagl<=r;tagl++){//point to the first negative num or r+1
		if(a[tagl]<0)break;
		ansl*=a[tagl];
		if(ansl>M){
			cout<<"Too large"<<"\n";
			return;
		}	
	}
	for(tagr=r;tagr>=l;tagr--){
		if(a[tagr]<0)break;
		ansr*=a[tagr];
		if(ansr>M){
			cout<<"Too large"<<"\n";
			return;
		}	
	}
	if(tagl>=tagr){//no negative num or only one
		cout<<max(ansl,ansr)<<"\n";
		return;
	}
	for(int i=tagl+1;i<=tagr-1;i++){
		ansm*=a[i];
		if(ansm>M||ansm<-M){//at least one negative num tagl to make ansm which<-M >M
			cout<<"Too large"<<"\n";
			return;
		}
	}
	if(ansm>0){
		ansm*=a[tagl];
		if(ansm>M||ansm<-M){
			cout<<"Too large"<<"\n";
			return;
		}
		ansm*=a[tagr];
		if(ansm>M){
			cout<<"Too large"<<"\n";
			return;
		}
		ansm*=ansl;
		if(ansm>M){
			cout<<"Too large"<<"\n";
			return;
		}
		ansm*=ansr;
		if(ansm>M){
			cout<<"Too large"<<"\n";
			return;
		}
		cout<<ansm<<"\n";
		return;
	}
	else{
		long long ans=1ll,temp=ansm;
		temp*=a[tagl];
		if(temp>M||temp<-M){
			cout<<"Too large"<<"\n";
			return;
		}
		temp*=ansl;
		if(temp>M){
			cout<<"Too large"<<"\n";
			return;
		}
		ans=max(temp,ansr);
		temp=ansm;
		temp*=a[tagr];
		if(temp>M){
			cout<<"Too large"<<"\n";
			return;
		}
		temp*=ansr;
		if(temp>M){
			cout<<"Too large"<<"\n";
			return;
		}
		ans=max(ans,max(temp,ansl));
		cout<<ans<<"\n";
		return;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int opt;
	while(q--){
		cin>>opt;
		if(opt==1){
			int i,k;
			cin>>i>>k;
			a[i]=k;
		}
		else{
			int l,r;
			cin>>l>>r;
			sol(l,r);
		}
	}
	return 0;
}
