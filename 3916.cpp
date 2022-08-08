#include<iostream>
#include<vector>
//#include<queue>
using namespace std;
const int MAXN=1e5+5;
int n,m;
int a[MAXN];
vector<int> t[MAXN];
int status[MAXN];
int finda(int i){
    if(status[i]==1)return 0;
    status[i]=2;
    a[i]=i;
    int fflag=0;
    for(int j:t[i]){
        if(status[j]==0){
            if(finda(j))fflag=1;
            a[i]=a[i]<a[j]?a[j]:a[i];
        }
        else if(status[j]==1){
            a[i]=a[i]<a[j]?a[j]:a[i];
        }
        else if(status[j]==2){
            fflag=1;
        }
    }
    if(fflag==0){
        status[i]=1;
    }
    else{
        status[i]=0;
    }
    //status[i]=1;
    return fflag;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int ss,ee;
    for(int i=0;i<m;i++){
        cin>>ss>>ee;
        t[ss].push_back(ee);
    }
    for(int i=1;i<=n;i++){
        finda(i);
        cout<<a[i]<<" ";
    }

    return 0;
}
