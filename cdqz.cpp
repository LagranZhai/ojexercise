#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int maxn=2e5;
struct Edge{
    int v{0},nxt{0};
}edg[maxn*3];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
}
int n,k;
int a[maxn*2];
int siz[maxn*2];
int dfn[maxn*2],rnk[maxn*2],tot{0};
void dfs(int x,int f){
    dfn[x]=++tot;
    rnk[tot]=x;
    siz[x]=1;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            dfs(to,x);
            siz[x]+=siz[to];
        }
    }
}
std::vector<int> val;
struct Que{
    int l,r,ans,index;
}que[maxn*2];
int c[maxn*2]{};
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i{1};i<=n;i++){
        cin>>a[i];
        val.push_back(a[i]);
    }
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u>>v;
        addedge(u,v);addedge(v,u);
    }
    dfs(1,0);
    std::sort(std::begin(val),std::end(val));
    val.erase(std::unique(std::begin(val),std::end(val)),std::end(val));
    for(int i{1};i<=n;i++){
        rnk[i]=std::lower_bound(std::begin(val),std::end(val),a[rnk[i]])-std::begin(val)+1;
    }
    int q,x;
    cin>>q;
    int block=std::sqrt(q);
    for(int i{1};i<=q;i++){
        cin>>x;
        que[i].l=dfn[x];que[i].r=dfn[x]+siz[x]-1;
        que[i].index=i;
    }
    std::sort(que+1,que+q+1,[block](const Que A,const Que B){
        if(A.l/block==B.l/block){
            if((A.l/block)%2==1)return A.r<B.r;
            else return A.r>B.r;
        }
        else return A.l<B.l;
    });
    int l{0},r{-1},ans{0};
    for(int i{1};i<=q;i++){
        // cout<<que[i].l<<que[i].r;
        while(r<que[i].r){
            r++;
            if(c[rnk[r]]==k){
                ans--;
            }
            c[rnk[r]]++;
            if(c[rnk[r]]==k){
                ans++;
            }
        }
        while(l>que[i].l){
            l--;
            if(c[rnk[l]]==k){
                ans--;
            }
            c[rnk[l]]++;
            if(c[rnk[l]]==k){
                ans++;
            }
        }
        while(r>que[i].r){
            if(c[rnk[r]]==k){
                ans--;
            }
            c[rnk[r]]--;
            if(c[rnk[r]]==k){
                ans++;
            }
            r--;
        }
        while(l<que[i].l){
            if(c[rnk[l]]==k){
                ans--;
            }
            c[rnk[l]]--;
            if(c[rnk[l]]==k){
                ans++;
            }
            l++;
        }
        que[i].ans=ans;
    }
    std::sort(que+1,que+q+1,[](const Que A,const Que B){return A.index<B.index;});
    for(int i{1};i<=q;i++){
        cout<<que[i].ans<<"\n";
    }
    // cout<<block;
    cout.flush();
    return 0;
}