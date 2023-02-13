#include<bits/stdc++.h>
using namespace std;
const int maxm=60,maxn=3.2e4;
vector<int> a[maxm*2];
int val[maxm*2],w[maxm*2];
bool mi[maxm*2];
int dp[maxn*2];
int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    int v,p,q;
    for(int i=1;i<=m;i++){
        cin>>v>>p>>q;
        val[i]=v*p;w[i]=v;
        if(q!=0){
            a[q].push_back(i);
            mi[i]=0;
        }
        else mi[i]=1;
    }
    for(int i=1;i<=m;i++){
        if(!mi[i])continue;
        for(int j=n;j>w[i];j--){
            dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
            if(!a[i].empty()){
                if(j-w[a[i][0]]-w[i]>=0)
                    dp[j]=max(dp[j],dp[j-w[a[i][0]]-w[i]]+val[i]+val[a[i][0]]);
                if((int)a[i].size()>1){
                    if(j-w[a[i][1]]-w[i]>=0)
                        dp[j]=max(dp[j],dp[j-w[a[i][1]]-w[i]]+val[i]+val[a[i][1]]);
                    if(j-w[a[i][0]]-w[a[i][1]]-w[i]>=0)
                        dp[j]=max(dp[j],dp[j-w[a[i][0]-w[a[i][1]]]-w[i]]+val[i]+val[a[i][0]]+val[a[i][1]]);
                }
            }
        }
    }
    cout<<dp[n]<<endl;
    return 0;
}