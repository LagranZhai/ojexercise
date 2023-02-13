#include<bits/stdc++.h>
using namespace std;
const int maxm=60;
vector<int> a[maxm*2];
int val[maxm*2],w[maxm*2];
bool mi[maxm*2];
int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    int v,p,q;
    for(int i=1;i<=m;i++){
        cin>>v>>p>>q;
        val[i]=v;w[i]=p;
        if(q!=0){
            a[q].push_back(i);
            mi[i]=0;
        }
        else mi[i]=1;
    }
    for(int i=1;i<=n;i++){
        if(!mi[i])continue;
        for(int j=n;j>w[i];j--){
            for(auto )
        }
    }
    return 0;
}