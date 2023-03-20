#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=1e8;
int vis[maxn+100],pri[maxn],cnt=0;
void init(int n){
  for(int i=2;i<=n;i++){
    if(!vis[i]){
      pri[++cnt]=i;
    }
    for(int j=1;j<=cnt;j++) {
      if(1ll*i*pri[j]>n)break;
      vis[i*pri[j]]=1;
      if(i%pri[j]==0)break;
    }
  }
}
int main(){
    ios::sync_with_stdio(false);
    int n,q;
    cin>>n>>q;
    init(n);
    int x;
    for(int i=1;i<=q;i++){
        cin>>x;
        cout<<pri[x]<<'\n';
    }
    return 0;
}
