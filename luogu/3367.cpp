#include<iostream>
#include<cstring>
using namespace std;
int fa[10003],size[10003],depth[10003];
int findf(int i){
	return i==fa[i]?i:(fa[i]=findf(fa[i]));
}
int findfs(int i){
	if(i==fa[i])return i;
	findfs(fa[i]);
}
void mergeset(int i,int j){
	fa[findf(i)]=findf(j);
}
void mergesets(int i,int j){
	int ifa=findfs(i),jfa=findfs(j);
	if(size[ifa]>size[jfa]){
		fa[jfa]=ifa;
		size[i]+=size[j];
	}
	else{
		fa[ifa]=jfa;
		size[j]+=size[i];
	}
}
void mergesetd(int i,int j){
	int ifa=findfs(i),jfa=findfs(j);
	if(depth[ifa]>depth[jfa]){
		fa[jfa]=ifa;
	}
	else{
		fa[ifa]=jfa;
	}
	if(depth[ifa]==depth[jfa])depth[jfa]+=1;
}
string ans;
int main(){
	ios::sync_with_stdio(false); 
	int n,m;
	cin>>n>>m;
	int z,x,y;
	for(int i=0;i<n;i++){
		fa[i]=i;
		size[i]=1;
	}
	for(int i=0;i<m;i++){
		cin>>z>>x>>y;
		if(z==1){
			mergesetd(x,y);
		}
		else{
			if(findfs(x)==findfs(y)){
				ans+="Y\n";
			}
			else{
				ans+="N\n";
			}
		}
	}
	cout<<ans;
	
	return 0;
}





