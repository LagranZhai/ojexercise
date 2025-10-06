#include<bits/stdc++.h>
using std::cin,std::cout;
int main(){
    std::ios::sync_with_stdio(false);
    int n,m,s,t;
    cin>>n>>m;
    std::vector<int> deg(n+1);
    for(int i{};i<m;i++){
        cin>>s>>t;
        deg[s]++;deg[t]++;
    }
    long long ans{};
    for(int i{1};i<=n;i++){
        ans+=(n-1)-((n-1-deg[i])%2);
    }
    cout<<ans/2<<std::endl;
    return 0;
}