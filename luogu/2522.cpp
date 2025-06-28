//P2522
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=5e4+100;
int miu[maxn];
int vis[maxn];
std::vector<int> pri;
void euler(){
    miu[1]=1;
    for(int i{2};i<maxn;i++){
        if(!vis[i]){
            miu[i]=-1;
            pri.push_back(i);
        }
        for(int a:pri){
            if(a*i>=maxn)break;
            if(i%a==0){
                miu[i*a]=0;
                vis[i*a]=1;
                break;
            }
            vis[i*a]=1;
            miu[i*a]=-1*miu[i];
        }
    }
    for(int i{1};i<maxn;i++){
        miu[i]=miu[i-1]+miu[i];
    }
}
int a,b,c,d,k;
int get(int x,int y){
    if(x<k||y<k)return 0;
    x/=k;y/=k;
    int l{1},r{1},n{std::min(x,y)};
    int ans{0};
    while(l<=n){
        r=std::min(x/(x/l),y/(y/l));
        r=std::min(r,n);
        ans+=(miu[r]-miu[l-1])*((x)/l)*((y)/l);
        l=r+1;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;
    euler();
    // for(int i{1};i<=10;i++)cout<<miu[i]<<" ";
    for(int i{1};i<=n;i++){
        cin>>a>>b>>c>>d>>k;
        cout<<get(b,d)-get(a-1,d)-get(b,c-1)+get(a-1,c-1)<<"\n";
    }
    cout.flush();
    return 0;
}