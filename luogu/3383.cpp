#include<algorithm>
#include<iostream>
using namespace std;
using ll=long long;
constexpr int maxn=1e3;
consteval std::vector<int > init(){
  int vis[maxn+100]={},n=maxn;
  vector<int > pri;
  for(int i=2;i<=n;i++){
    if(!vis[i]){
      pri.push_back(i);
    }
    for(int j=0;j<pri.size();j++) {
      if(1ll*i*pri[j]>n)break;
      vis[i*pri[j]]=1;
      if(i%pri[j]==0)break;
    }
  }
  return pri;
}
int main(){
    constexpr auto pri=init();
    ios::sync_with_stdio(false);
    int n,q;
    cin>>n>>q;
    int x;
    for(int i=1;i<=q;i++){
        cin>>x;
        int v=pri[x-1];
        cout<<v<<'\n';
    }
    return 0;
}
