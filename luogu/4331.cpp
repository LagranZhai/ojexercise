#include<bits/stdc++.h>
using std::cin,std::cout;
constexpr int maxn=1e6+10;
long long a[maxn]{},n{},low[maxn];
int main(){
    std::ios::sync_with_stdio(false);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
        a[i]-=i;
    }
    std::priority_queue<long long> q;
    long long ans{};
    for(int i{1};i<=n;i++){
        if(q.empty()){
            q.push(a[i]);
            low[i]=a[i];
            continue;
        }
        int cur{q.top()};
        q.push(a[i]);q.push(a[i]);q.pop();
        ans+=std::max(0ll,cur-a[i]);
        low[i]=q.top();
    }
    cout<<ans<<std::endl;
    long long las{std::numeric_limits<long long>::max()};
    std::vector<long long> res{};
    for(int i{n};i>=1;i--){
        if(low[i]<las){
            res.push_back(low[i]+i);
            las=low[i];
        }
        else{
            res.push_back(las+i);
        }
    }
    std::reverse(res.begin(),res.end());
    for(auto i:res){
        cout<<i<<" ";
    }
    cout.flush();
    return 0;
}
