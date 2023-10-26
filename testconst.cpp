#include<iostream>
#include<array>
constexpr int maxn=1.1e5;
constexpr std::array<long long ,maxn > init(){
    std::array<long long ,maxn > pri{};
    std::array<bool ,maxn+100 > vis{};
    int cnt{0};
    for(int i=2;i<=maxn;i++){
        if(!vis[i]){
            pri[++cnt]=i;
        }
        for(int j=1;j<=cnt;j++){
            if(1ll*i*pri[j]>maxn)break;
            vis[i*pri[j]]=1;
            if(i%pri[j]==0)break;
        }
    }
    return pri;
}
constexpr std::array<long long ,maxn > pri{
init()
};
int main(){
    // std::ios::sync_with_stdio(false);
    // int n,q;
    // std::cin>>n>>q;
    // // init((int)1e8);
    // int x;
    // for(int i=1;i<=q;i++){
    //     std::cin>>x;
    int n;std::cin>>n;
        std::cout<<pri[n]<<'\n';
    // }
    // std::cout<<std::flush;
    return 0;
}