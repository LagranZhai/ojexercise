//PC
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=20,base=11;
int a[maxn][maxn],b[maxn][maxn];
int n,m;
std::map<int,int> map;
std::vector<int> unzip(int x){
    std::vector<int> res;
    for(int i{1};i<=n;i++){
        res.push_back(x%base);
        x/=base;
    }
    return res;
}
int dfs(int x){
    if(map.find(x)!=map.end()){
        return map[x];
    }
    std::vector<int> cur{unzip(x)};
    int cnt{0};
    for(int a:cur){
        cnt+=a;
    }
    if(cnt==n*m){
        map[x]=0;
        return 0;
    }
    if(cnt%2==0){
        int ans{std::numeric_limits<int>::min()};
        if(cur[0]!=m){
            ans=std::max(ans,dfs(x+1)+a[1][cur[0]+1]);
        }
        int now{1};
        for(int i{1};i<n;i++){
            now*=base;
            if(cur[i]!=cur[i-1]&&cur[i]!=m){
                ans=std::max(ans,dfs(x+now)+a[i+1][cur[i]+1]);
            }
        }
        return map[x]=ans;
    }
    else{
        int ans{std::numeric_limits<int>::max()};
        if(cur[0]!=m){
            ans=std::min(ans,dfs(x+1)-b[1][cur[0]+1]);
        }
        int now{1};
        for(int i{1};i<n;i++){
            now*=base;
            if(cur[i]!=cur[i-1]&&cur[i]!=m){
                ans=std::min(ans,dfs(x+now)-b[i+1][cur[i]+1]);
            }
        }
        return map[x]=ans;
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            cin>>b[i][j];
        }
    }
    cout<<dfs(0)<<"\n";
    cout.flush();
    return 0;
}