#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=2e5;
#define int long long
constexpr int p=19260817;
std::vector<int > a[maxn+10];
std::vector<int > dp[maxn+10];
std::vector<int > all;
std::vector<int > m[maxn+10];
std::set<int > colrow[maxn+10];
std::vector<int > col;
std::vector<int > item[maxn+10];
std::vector<int > itemset[maxn+10];
std::vector<int > nxt[maxn+10];
int pi=1;
// std::vector<int > c[maxn+10];
int l[maxn+10];
int n,q;
int s[maxn+10];
int inv[maxn+10];
int qpow(int a,int b){
    int c=1;
    while(b){
        if(b&1)c=c*a%p;
        a=a*a%p;
        b>>=1;
    }
    return c;
}
struct modify{
    int x,y,z;
}modi[maxn+10];
int cnt=0;
int aa;
int getcol(int x){
    return std::lower_bound(std::begin(all),std::begin(all)+aa,x)-std::begin(all);
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    for(int i{1};i<=n;i++){
        cin>>l[i];
    }
    int t;
    for(int i{1};i<=n;i++){
        for(int j{1};j<=l[i];j++){
            int t;
            cin>>t;
            a[i].push_back(t);
            all.push_back(t);
            s[i]=(s[i]+j*(l[i]-j+1)%p)%p;   
        }
        inv[i]=qpow(s[i],p-2);
        pi=pi*s[i]%p;
    }
    for(int i{1};i<=q;i++){
        ++cnt;
        cin>>modi[cnt].x>>modi[cnt].y>>modi[cnt].z;
        all.push_back(modi[cnt].z);
    }
    aa=std::unique(std::begin(all),std::end(all))-std::begin(all);
    std::sort(std::begin(all),std::begin(all)+aa);
    for(int i{1};i<=n;i++){
        nxt[i].resize(l[i]+10);
        dp[i].resize(l[i]+10);
        item[i].resize(l[i]+10);
        m[i].resize(l[i]+10);
        for(int j{0};j<a[i].size();j++){
            if(colrow[i].empty()||colrow[i].find(getcol(a[i][j]))==colrow[i].end()){
                m[i][getcol(a[i][j])]=j+1;
                nxt[i][getcol(a[i][j])]=j+1;
                // dp[i][getcol(a[i][j])]=(dp[i][getcol(a[i][j])]+(j+1)*(l[i]-j)%p)%p;
            }
            else{
                dp[i][getcol(a[i][j])]=(dp[i][getcol(a[i][j])]+nxt[i][getcol(a[i][j])]*(l[i]-j)%p)%p;
                // dp[i][getcol(a[i][j])]=(dp[i][getcol(a[i][j])]+p)%p;
                nxt[i][getcol(a[i][j])]=j+1;
                // dp[i][getcol(a[i][j])]=(dp[i][getcol(a[i][j])]+(j+1)*(l[i]-j)%p)%p;
            }
            if(colrow[i].empty()){
                colrow[i].insert(getcol(a[i][j]));
            }
            else{
                if(colrow[i].find(getcol(a[i][j]))==colrow[i].end()){
                    colrow[i].insert(getcol(a[i][j]));
                }
            }
        }
        for(auto j:colrow[i]){
            item[i][j]=dp[i][j]*inv[i]%p;
            itemset[j].push_back(item[i][j]);
        }
        
        // cout<<std::endl;
    }
    int ans=0;
    for(int i{0};i<aa;i++){
        int res=1;
        for(int j{0};j<itemset[i].size();j++){
            res=res*((1-itemset[i][j]+p)%p)%p;
        }
        ans=(ans+res)%p;
    }
    ans=ans*pi%p;
    cout<<ans<<std::endl;
    return 0;
}