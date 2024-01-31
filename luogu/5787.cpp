//P5787
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=1e5,maxm=2e5;
int n,m,k;
using pii=std::pair<int,int>;
std::vector<pii> tree[maxn*4];
int status{1};
void update(int p,int cl,int cr,const int l,const int r,const int x,const int y){
    if(cl>=l&&cr<=r){
        tree[p].push_back({x,y});
        return ;
    }
    if(cl!=cr){
        int mid{(cl+cr)/2};
        if(l<=mid){
            update(p*2,cl,mid,l,r,x,y);
        }
        if(r>mid){
            update(p*2+1,mid+1,cr,l,r,x,y);
        }        
    }
}
int fa[maxn*2],dep[maxn*2],val[maxn*2];
pii getfa(int x){
    if(fa[x]!=x){
        pii t{getfa(fa[x])};
        return {t.first,t.second^val[x]};
    }
    else{
        return {x,0};
    }
}
using ppi=std::pair<int*,int>;
void merge(int x,int y,std::stack<ppi> &s){
    pii fx{getfa(x)},fy{getfa(y)};
    if(fx.first==fy.first){
        if((fx.second^fy.second)==0){
            s.push({&status,status});
            status=0;
        }
    }
    else{
        if(dep[fy.first]<dep[fx.first]){
            std::swap(fx,fy);
        }
        s.push({&val[fx.first],val[fx.first]});
        val[fx.first]=fy.second^fx.second^1;
        s.push({&fa[fx.first],fa[fx.first]});
        fa[fx.first]=fy.first;
        if(dep[fy.first]==dep[fx.first]){
            s.push({&dep[fy.first],dep[fy.first]});
            dep[fy.first]++;
        }
    }
}
void dfs(int p,int cl,int cr){
    std::stack<ppi> s;
    if(status){
        for(pii a:tree[p]){
            merge(a.first,a.second,s);
            if(status==0)break;
        }
    }
    if(cl==cr){
        cout<<(status?"Yes\n":"No\n");
        while(!s.empty()){
            ppi t{s.top()};
            *t.first=t.second;
            s.pop();
        }
        return ;
    }
    int mid{(cl+cr)/2};
    dfs(p*2,cl,mid);
    dfs(p*2+1,mid+1,cr);
    while(!s.empty()){
        ppi t{s.top()};
        *t.first=t.second;
        s.pop();
    }
    return ;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m>>k;
    for(int i{1};i<=n;i++){
        fa[i]=i;
        dep[i]=1;
        val[i]=1;
    }
    int x,y,l,r;
    for(int i{1};i<=m;i++){
        cin>>x>>y>>l>>r;
        update(1,1,n,l+1,r,x,y);
    }
    dfs(1,1,n);
    cout.flush();
    return 0;
}