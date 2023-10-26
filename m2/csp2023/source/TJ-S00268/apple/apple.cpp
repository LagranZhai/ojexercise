#include<bits/stdc++.h>
using std::cin;using std::cout;using std::ios;
constexpr int maxn=5e4;
struct Edge{
    int v{0},nxt{0};
}edg[maxn*2];
int head[maxn*2],cnt{0};
void addedge(int u,int v){
    edg[++cnt].v=v;
    edg[cnt].nxt=head[u];
    head[u]=cnt;
    return ;
}
bool des[maxn*2];
int n,k;
int fa[maxn*2],ch[maxn*2],val[maxn*2];
struct Node{
    int w{0},p{0};
    bool operator<(const Node A)const{
        if(w==A.w){
            return p<A.p;
        }
        else return w>A.w;
    }
};
std::set<Node > s;
void dfs(int x,int f){
    if(f==-1)val[x]=0;
    else val[x]=val[f]+1;
    fa[x]=f;
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f){
            ch[x]++;
            dfs(to,x);
        }
    }
    if(ch[x]==0){
        s.insert({val[x],x});
    }
}
void reval(int x,int f,bool rt){
    if(des[x]==0&&ch[x]==0){
        s.erase({val[x],x});
    }
    if(rt)val[x]=0;
    else val[x]=val[f]+1;
    if(des[x]==0&&ch[x]==0){
        s.insert({val[x],x});
    }
    for(int e{head[x]};e;e=edg[e].nxt){
        int to{edg[e].v};
        if(to!=f&&des[to]==0){
            reval(to,x,0);
        }
    }
    return ;
}
int main(){
    freopen("apple.in","r",stdin);
    freopen("apple.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>k;
    int u,v;
    for(int i{1};i<n;i++){
        cin>>u;
        addedge(i,u);
        addedge(u,i);
    }
    des[k]=1;
    cout<<k<<"\n";
    dfs(k,-1);
    int t;
    while(!s.empty()){
//        cin>>t;
        Node cur{*s.begin()};
        s.erase(s.begin());
        cout<<cur.p<<"\n";
//        des[cur.p]=1;
        int f=cur.p;
        while(fa[f]!=-1){
            des[f]=1;
            if(des[fa[f]]==1){
                break;
            }
            else{
                f=fa[f];
            }
        }
        reval(f,fa[f],1);
    }
    cout<<std::endl;
//    for(auto i:s){
//        cout<<i.p<<"\n";
//    }
    return 0;
}
