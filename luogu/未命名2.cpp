#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
const long long mm=1073741824ll;
int n,q,tag[550],s[550];
long long a[maxn],b[550];
int main(){
	ios::sync_with_stdio(false);
	//freopen("T1ex1.in","r",stdin);
	cin>>n>>q;
	int len=sqrt(n);
	for(int i=1;i<=550;i++){
		b[i]=1;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i%len==0){
			b[i/len]*=a[i];
			if(a[i]<0)tag[i/len]+=1;
			s[i/len]++;
		}
		else{
			b[i/len+1]*=a[i];
			if(a[i]<0)tag[i/len+1]+=1;
			s[i/len+1]++;
		}
	}
	int tot=(n%len==0)?(n/len):(n/len+1);
	int opt;
	while(q--){
		cin>>opt;
		if(opt==1){
			int i,k;
			cin>>i>>k;
			int j=(i%len==0)?(i/len):(i/len+1);
			b[j]=b[j]/a[i]*k;
			if(a[i]<0)tag[j]--;
			if(k<0)tag[j]++;
			a[i]=k;
		}
		else{
			int l,r;
			cin>>l>>r;
			int jl,jr;
			jl=(l%len==0)?(l/len):(l/len+1);
			jr=(r%len==0)?(r/len):(r/len+1);
			int tagl=0,tagr=0,tagjl=0,tagjr=0,tagm=0;
			long long ansl=1ll,ansr=1ll,ansm=1ll,ans=1ll;
			for(int i=l;i<=jl*len&&i<=r;i++){
				if(a[i]<0){
					tagl=i;
					break;
				}
				ansl*=a[i];
				
			}
			if(tagl==0){
				tagjl=jl+1;
				for(;tagjl<jr;tagjl++){
					if(tag[tagjl]>0){
						break;
					}
					ansl*=b[tagjl];
				}				
				for(int i=len*(tagjl-1)+1;i<=len*tagjl&&i<=r;i++){
					if(a[i]<0){
						tagl=i;
						break;
					}
					ansl*=a[i];
				}
				
			}
			
			for(int i=r;i>=(jr-1)*len+1&&i>=l;i--){
				if(a[i]<0){
					tagr=i;
					break;
				}
				ansr*=a[i];
			}
			if(tagr==0){
				tagjr=jr-1;
				for(;tagjr>jl;tagjr--){
					if(tag[tagjr]>0){
						break;
					}
					ansr*=b[tagjr];
				}				
				for(int i=len*tagjr;i>=len*(tagjr-1)+1&&i>=l;i--){
					if(a[i]<0){
						tagr=i;
						break;
					}
					ansr*=a[i];
				}
				
			}
			if(tagl==tagr){
				ans=max(ansl,ansr);
				ans=max(ans,1ll);
				if(ans>mm)cout<<"Too large\n";
				else cout<<ans<<"\n";
			}
			else{
				tagjl=(tagl%len==0)?(tagl/len):(tagl/len+1);
				tagjr=(tagr%len==0)?(tagr/len):(tagr/len+1);
				for(int i=tagl+1;i<=tagjl*len;i++){
					if(a[i]<0)tagm++;
					ansm*=a[i];
				}
				tagjl++;
				for(;tagjl<jr;tagjl++){
					ansm*=b[tagjl];
					tagm+=tag[tagjl];
				}
				for(int i=(tagjl-1)*len+1;i<tagr;i++){
					if(a[i]<0)tagm++;
					ansm*=a[i];
				}
				if(tagm%2==0){
					ans=ansl*ansm*ansr*a[tagl]*a[tagr];
					if(ans>mm)cout<<"Too large\n";
					else cout<<ans<<"\n";
				}
				else{
					long long ans1=max(ansl,ansm*a[tagr]*ansr);
					long long ans2=max(ansr,ansm*a[tagl]*ansl);
					ans=max(ans1,ans2);
					if(ans>mm)cout<<"Too large\n";
					else cout<<ans<<"\n";
				}
			}
		}
	}
	return 0;
}
