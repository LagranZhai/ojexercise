#include<iostream>
#include<vector>
//#include<queue>
using namespace std;
const int MAXN=1e5+5;
int n,m;
int a[MAXN],fa[MAXN];
int ffind(int i){
	return fa[i]=((fa[i]==i)?i:ffind(fa[i]));
}
vector<int> t[MAXN];
int status[MAXN];
int finda(int i){
	i=ffind(i);
    if(status[i]==1)return a[i];
    status[i]=2;
    a[i]=i;
    //int fflag=0;
    for(int j=0;j<t[i].size();j++){
    	j=ffind(j);
        if(status[j]==0){
            //if(finda(j))fflag=1;
            a[i]=max(a[i],finda(j));
            if(fa[j]!=j)fa[ffind(j)]=ffind(i);
        }
        else if(status[j]==1){
            a[i]=max(a[i],a[j]);
        }
        else if(status[j]==2){
            //fflag=1;
            fa[i]=ffind(j);
        }
    }
    //if(fflag==0){
    status[i]=1;
    return a[i];
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    //init
    for(int i=1;i<=n;i++){
    	fa[i]=i;
	}
    int ss,ee;
    for(int i=0;i<m;i++){
        cin>>ss>>ee;
        t[ss].push_back(ee);
    }
    for(int i=1;i<=n;i++){
        cout<<finda(i)<<" ";
    }

    return 0;
}
