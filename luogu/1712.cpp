#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=6e5;
#define int long long
int n,m;
struct Range{
    int l,r;
    int sl,sr;
}rg[maxn*2];
struct Data{
    int max{0};
    Data operator+(Data A){
        return {std::max(max,A.max)};
    }
};
struct Tag{
    int add{0};
    Tag operator+(Tag A){
        return {add+A.add};
    }
    Data operator*(Data A){
        return {A.max+add};
    }
};
struct dm{
    Data d{};Tag t{};
}tree[maxn*4];
void pushdown(int p){
    if(tree[p].t.add!=0){
        tree[p*2].d=tree[p].t*tree[p*2].d;
        tree[p*2].t=tree[p].t+tree[p*2].t;
        tree[p*2+1].d=tree[p].t*tree[p*2+1].d;
        tree[p*2+1].t=tree[p].t+tree[p*2+1].t;
        tree[p].t=Tag{};    
    }
}
void update(int p,int cl,int cr,int l,int r,Tag w){
    if(cl>=l&&cr<=r){
        tree[p].d=w*tree[p].d;
        tree[p].t=w+tree[p].t;
        return ;
    }
    if(cl!=cr){
        pushdown(p);
        int mid{(cl+cr)/2};
        if(l<=mid)update(p*2,cl,mid,l,r,w);
        if(r>mid)update(p*2+1,mid+1,cr,l,r,w);
        tree[p].d=tree[p*2].d+tree[p*2+1].d;
        return ;
    }
}
void query(int p,int cl,int cr,int l,int r,Data &ans){
    if(cl>=l&&cr<=r){
        ans=ans+tree[p].d;
        return ;
    }
    if(cl!=cr){
        pushdown(p);
        int mid{(cl+cr)/2};
        if(l<=mid)query(p*2,cl,mid,l,r,ans);
        if(r>mid)query(p*2+1,mid+1,cr,l,r,ans);
        return ;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    std::vector<int> v;
    for(int i{1};i<=n;i++){
        cin>>rg[i].l>>rg[i].r;
        v.push_back(rg[i].l);
        v.push_back(rg[i].r);
    }
    std::sort(std::begin(v),std::end(v));
    v.erase(std::unique(std::begin(v),std::end(v)),std::end(v));
    int nn=v.size();
    for(int i{1};i<=n;i++){
        rg[i].sl=std::lower_bound(std::begin(v),std::end(v),rg[i].l)-std::begin(v)+1;
        rg[i].sr=std::lower_bound(std::begin(v),std::end(v),rg[i].r)-std::begin(v)+1;
    }
    auto len=[](const Range a){return a.r-a.l;};
    std::sort(rg+1,rg+n+1,[=](const Range &a,const Range &b){
        return len(a)<len(b);
    });
    int l{0},r{0};
    int ans{-1};
    while(r<n){
        ++r;
        update(1,1,nn,rg[r].sl,rg[r].sr,{1});
        while([=](){Data ans{0};query(1,1,nn,1,nn,ans);return ans.max>=m;}()){
            if(ans!=-1)ans=std::min(ans,len(rg[r])-len(rg[l]));
            else ans=len(rg[r])-len(rg[l]);
            update(1,1,nn,rg[l].sl,rg[l].sr,{-1});
            l++;
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}