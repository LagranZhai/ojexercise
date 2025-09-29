#include<bits/stdc++.h>
using std::cin,std::cout;
int main(){
    std::ios::sync_with_stdio(false);
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        std::vector<int> a(n+1),mx(n+1),lst(n+1),dp(n+1);
        for(int i{1};i<=n;i++){
            cin>>a[i];
        }
        std::vector<std::queue<int>> pos(n+1);
        for(int i{1};i<=n;i++){
            auto& q=pos[a[i]];
            if(q.size()<a[i]){
                q.push(i);
            }
            else{
                q.pop();q.push(i);
            }
            if(q.size()==a[i]){
                lst[i]=q.front();
            }
            else{
                lst[i]=0;
            }
        }
        for(int i{1};i<=n;i++){
            if(lst[i]!=0){
                dp[i]=mx[lst[i]-1]+a[i];
            }
            mx[i]=std::max(mx[i-1],dp[i]);
        }
        cout<<mx[n]<<"\n";
    }
    return 0;
}