#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e4,P=998244353;
#define int long long
int p[maxn*2];
int n,w;
bool vis[maxn*2];
int pri[maxn*2];
int cnt{0};
void euler(){
    for(int i{2};i<maxn;i++){
        // std::cerr<<i<<" ";
        if(vis[i]==0){
            pri[++cnt]=i;
        }
        for(int j{1};j<=cnt;j++){
            if(pri[j]*i>=maxn)break;
            vis[i*pri[j]]=1;
            if(i%pri[j]==0)break;
        }
    }
}
void broke(int n,std::vector<std::pair<int,int> > &res){
    // std::vector<std::pair<int,int> > res;
    for(int i{1};i<=cnt;i++){
        if(n==1)break;
        if(n%pri[i]==0){
            int c{0};
            while(n%pri[i]==0){
                c++;
                n/=pri[i];
            }
            res.push_back({pri[i],c});
        }
    }
    // return res;
}
std::vector<std::pair<int,int> > bp[maxn*2];
std::vector<std::pair<int,int> > bw;
int bcnt[maxn*2];
__int128 dp[maxn*2][30];
int myr[maxn*2];
signed main(){
    // freopen("plant.in","r",stdin);
    // freopen("plant.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>w;
    for(int i{1};i<=n;i++){
        cin>>p[i];
    }
    euler();
    for(int i{1};i<=n;i++){
        broke(p[i],bp[i]);
    }
    broke(w,bw);
    unsigned int ans{1};
    for(auto a:bw){
        int p{a.first},num{a.second};
        std::fill(dp[0],dp[0]+maxn*20,0);
        dp[0][0]=1;
        std::vector<int> tmp;
        for(int i{1};i<=n;i++){
            int r{1};
            for(auto b:bp[i]){
                if(b.first==p)r+=b.second;
            }
            tmp.push_back(r);
        }
        std::sort(std::begin(tmp),std::end(tmp));
        for(int i{0};i<tmp.size();i++){
            if(i+1<=num){
                myr[i+1]=tmp[i];
            }
            else{
                ans=ans*(tmp[i])%P;
            }
        }
        for(int i{1};i<=num;i++){
            int r{myr[i]};
            for(int j{0};j<=num;j++){
                // dp[i][j]=dp[i-1][j];
                for(int k{1};k<=j;k++){
                    dp[i][j]=std::max(dp[i][j],dp[i-1][j-k]*(r+k));
                }
            }
        }
        // if(dp[num][num]==0){
        //     cout<<p<<" "<<num<<"a";
        // }
        ans=ans*(dp[num][num]%P)%P;
    }
    for(auto a:bw){
        bcnt[a.first]=a.second;
        // cout<<a.first<<"  ";
    }
    for(int i{1};i<=n;i++){
        for(auto a:bp[i]){
            if(bcnt[a.first]==0){
                ans=ans*(a.second+1)%P;
            }
        }
    }
    cout<<ans%P<<"\n";
    cout.flush();
    return 0;
}