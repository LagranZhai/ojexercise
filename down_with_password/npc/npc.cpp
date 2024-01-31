#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=10,P=998244353;
#define int long long
int n,t;
int a[maxn*2];
int v[maxn*2];
int lowbit(int x){
    return x&(-x);
}
int getv(int x){
    x=lowbit(x);
    int cnt{0};
    while(x>0){
        cnt++;
        x>>=1;
    }
    return cnt;
}
signed main(){
    freopen("npc.in","r",stdin);
    freopen("npc.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin>>q;
    while(q--){
        cin>>n>>t;
        std::vector<int> ans;
        for(int i{1};i<=n;i++){
            a[i]=i;
        }
        do{
            for(int i{1};i<=n;i++){
                v[i]=getv(a[i]);
            }
            for(int i{1};i<=n;i++){
                v[i]=(v[i-1]+v[i])%P;
            }
            int res{0};
            for(int i{1};i<=n;i++){
                for(int j{0};j<i;j++){
                    res=(res+v[i]-v[j])%P;
                }
            }
            ans.push_back(res);
        }while(std::next_permutation(a+1,a+n+1));
        std::sort(std::begin(ans),std::end(ans));
        cout<<ans[t-1]<<"\n";
    }
    
    cout.flush();
    return 0;
}