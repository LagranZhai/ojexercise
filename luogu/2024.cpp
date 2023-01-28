#include<iostream>
#include<cstring>
using namespace std;
int fa[50015],val[50015];
int findf(int i){
	if(i==fa[i]){
		return i;
	}
	int ff=fa[i];
	fa[i]=findf(ff);
//	if(!val[i]){
//		val[i]=val[ff];
//	}
//	else if(val[i]==val[ff]){
//		if(val[i]==1)val[i]++;
//		else if(val[i]==2){
//			val[i]--;
//		}		
//	}
//	else if(val[i]+val[ff]==3){
//		val[i]=0;
//	} 
	val[i]=(val[i]+val[ff])%3; 
	return fa[i]; 
}
void merge(int i,int j,int opt){
	int fj=findf(j);
	int fi=findf(i);
	//if(fa[i]!=fi)cout<<1;
	if(opt==0){
		//if(fa[i]!=fi)cout<<1;
		fa[fa[i]]=fa[j];
//		if(val[i]==0)val[fa[i]]=val[j];
//		else{
//			 if(val[i]==1){
//				if(val[j]==1){
//					val[fa[i]]=0;
//				}
//				else if(val[j]==0){
//					val[fa[i]]=2;
//				}
//				else{
//					val[fa[i]]=1;
//				}
//			}
//			else if(val[i]==2){
//			   	if(val[j]==1){
//					val[fa[i]]=2;
//				}
//				else if(val[j]==0){
//					val[fa[i]]=1;
//				}
//				else{
//					val[fa[i]]=0;
//				}
//			}
//		}
		val[fi]=(val[j]-val[i]+3)%3; 
	}
	else if(opt==1){
		fa[fa[i]]=fa[j];
//		if(val[i]==1)val[fa[i]]=val[j];
//		else{
//			if(val[i]==2){
//				if(val[j]==1){
//					val[fa[i]]=0;
//				}
//				else if(val[j]==0){
//					val[fa[i]]=2;
//				}
//				else{
//					val[fa[i]]=1;
//				}
//			}
//			else if(val[i]==0){
//			   	if(val[j]==1){
//					val[fa[i]]=2;
//				}
//				else if(val[j]==0){
//					val[fa[i]]=1;
//				}
//				else{
//					val[fa[i]]=0;
//				}
//			}
//		}
		val[fi]=(1+val[j]-val[i]+3)%3;
	}
}
int main(){
	ios::sync_with_stdio(false);
	freopen("P2024_2.in","r",stdin);
	int n,k;
	cin>>n>>k;
	int opt,x,y,cnt=0,ans[100003];
	for(int i=0;i<=n;i++){
		fa[i]=i;
		val[i]=0;
	}
	for(int i=0;i<k;i++){
		cin>>opt>>x>>y;
		opt--;
		if(x>n||y>n){
			cnt++;
			ans[cnt]=i+1;
			continue;
		}
		if(x==y&&opt==1){
			cnt++;
			ans[cnt]=i+1;
			continue;
		}
		//if(x==y&&opt==0)continue;
		
			int fx=findf(x);
			int fy=findf(y);
			if(fx==fy){				
				int tmp=0;
				tmp=(val[x]-val[y]+3)%3;
//				if(!tmp){
//					if(val[y]==1)tmp=2;
//					if(val[y]==2)tmp=1;
//				}
//				else if(tmp+val[y]==3){
//					tmp=val[y];
//				}
//				else if(tmp==val[y])tmp=0;
				if(tmp!=opt){
					cnt++;
					ans[cnt]=i+1;
				}
				else{
					merge(x,y,opt);
				}
			}
			else{
				merge(x,y,opt);
			}		
		
	}
//	for(int i=0;i<=cnt;i++){
//		cout<<ans[i];
//	}
	cout<<cnt;
	//fclose(stdin);
	
	
	return 0;
}
