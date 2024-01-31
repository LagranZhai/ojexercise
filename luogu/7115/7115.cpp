#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=50,maxm=400;
#define int long long
int n,m;
std::vector<int> zz[maxn+10];
std::vector<std::pair<int,int> > ans;
bool color(int a,int b,int c,int k){
    auto cmp{[k](bool f)->std::function<bool(int)> {
        auto less{[k](const int A){return A<=k;}};
        auto great{[k](const int A){return A>k;}};
        if(!f){
            return less;
        }
        else return great;
    }};
    int na=std::count_if(zz[a].begin(),zz[a].end(),cmp(0));
    int nb=std::count_if(zz[b].begin(),zz[b].end(),cmp(1));
    int nl=na+std::count_if(zz[b].begin(),zz[b].end(),cmp(0));
    int nr=nb+std::count_if(zz[a].begin(),zz[a].end(),cmp(1));
    bool flag{0};
    if(nl<nr){
        flag=1;
        std::swap(a,b);
        std::swap(na,nb);
    }
    if(na==m)return flag;
    auto moveball{[](int a,int b){
        zz[b].push_back(zz[a].back());
        zz[a].pop_back();
        ans.push_back({a,b});
    }};
    for(int i{1};i<=na;i++){
        moveball(b,c);
        // int t{zz[b].back()};
        // zz[b].pop_back();
        // zz[c].push_back(t);
        // ans.push_back({b,c});
    }
    for(int i{1};i<=m;i++){
        if(cmp(flag)(zz[a].back())){
            moveball(a,b);
        }
        else{
            moveball(a,c);
        }
    }
    for(int i{1};i<=na;i++){
        moveball(b,a);
    }
    for(int i{1};i<=m-na;i++){
        moveball(c,a);
    }
    for(int i{1};i<=na;i++){
        moveball(c,b);
    }
    for(int i{1};i<=m-na;i++){
        moveball(a,c);
    }
    int cnt{0};
    while(!zz[b].empty()){
        if(cmp(flag)(zz[b].back())){
            moveball(b,a);
            cnt++;
            if(cnt==m-na)break;
        }
        else{
            moveball(b,c);
        }
    }
    while(!zz[c].empty()){
        moveball(c,b);
    }
    return flag;
}
void solve(int l,int r){
    if(l==r){
        return ;
    }
    if(r==l+1){
        color(l,r,n+1,l);
        return ;
    }
    // cout<<" a";
    int mid{(l+r)/2};
    int p1{l},p2{mid+1};
    while(1){
        if(p1>mid&&p2>r)break;
        if(color(p1,p2,n+1,mid)){
            p2++;
        }
        else{
            p1++;
        }
    }
    solve(l,mid);
    solve(mid+1,r);
}
signed main(){
    // freopen("ball3.in","r",stdin);
    // freopen("ball.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    int t;
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            cin>>t;
            zz[i].push_back(t);
        }
    }
    solve(1,n);
    cout<<ans.size()<<"\n";
    for(auto a:ans){
        cout<<a.first<<" "<<a.second<<"\n";
    }
    cout.flush();
    return 0;
}