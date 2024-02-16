//PC
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=100,maxm=800;
std::vector<int> a[maxm];
int n,m;
using pii=std::pair<int,int>;
std::vector<pii> ans;
int trans(int x,int y,int mid){
    auto count=[mid](std::vector<int> &v){
        pii res{0,0};
        for(int i:v){
            if(i<=mid){
                res.first++;
            }
            else{
                res.second++;
            }
        }
        return res;
    };
    auto ban=[&](int u,int v){
        ans.push_back({u,v});
        int t{a[u].back()};
        a[u].pop_back();
        a[v].push_back(t);
    };
    pii cx{count(a[x])},cy{count(a[y])};
    int re{1};
    if(cx.first+cy.first==cx.second+cy.second){
        re=0;
    }
    else if(cx.first+cy.first<cx.second+cy.second){
        re=-1;
    }
    else{
        re=1;
    }
    if(cx.first+cy.first<=cx.second+cy.second){
        for(int i{1};i<=cy.first;i++){
            ban(x,n+1);
        }
        while(!a[y].empty()){
            int cur{a[y].back()};
            if(cur>mid){
                ban(y,n+1);
            }
            else{
                ban(y,x);
            }
        }
        for(int i{1};i<=cy.second;i++){
            ban(n+1,y);
        }
        for(int i{1};i<=cy.first;i++){
            ban(x,y);
        }
        for(int i{1};i<=cy.second;i++){
            ban(x,n+1);
        }
        for(int i{1};i<=cy.first;i++){
            ban(y,x);
        }
        while(!a[n+1].empty()){
            if(a[n+1].back()>mid&&a[y].size()<m){
                ban(n+1,y);
            }
            else{
                ban(n+1,x);
            }
        }
    }
    if(cx.first+cy.first>cx.second+cy.second){
        for(int i{1};i<=cx.second;i++){
            ban(y,n+1);
        }
        while(!a[x].empty()){
            int cur{a[x].back()};
            if(cur<=mid){
                ban(x,n+1);
            }
            else{
                ban(x,y);
            }
        }
        for(int i{1};i<=cx.first;i++){
            ban(n+1,x);
        }
        for(int i{1};i<=cx.second;i++){
            ban(y,x);
        }
        for(int i{1};i<=cx.first;i++){
            ban(y,n+1);
        }
        for(int i{1};i<=cx.second;i++){
            ban(x,y);
        }
        while(!a[n+1].empty()){
            if(a[n+1].back()<=mid&&a[x].size()<m){
                ban(n+1,x);
            }
            else{
                ban(n+1,y);
            }
        }
    }
    return re;
}
void fenzhi(int l,int r){
    if(l==r)return;
    int mid{(l+r)/2};
    int lp{l},rp{mid+1};
    while(lp<=mid||rp<=r){
        int res{trans(lp,rp,mid)};
        if(res==0){
            lp++;rp++;
        }
        else if(res==1){
            lp++;
        }
        else{
            rp++;
        }
    }
    fenzhi(l,mid);
    fenzhi(mid+1,r);
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int t;
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            cin>>t;
            a[i].push_back(t);
        }
    }
    fenzhi(1,n);
    cout<<ans.size()<<"\n";
    for(auto x:ans){
        cout<<x.first<<" "<<x.second<<"\n";
    }
    cout.flush();
    return 0;
}