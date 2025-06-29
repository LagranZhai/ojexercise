//P3919
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=1e6+100;
int n,m;
int root[maxn],cnt{0};
int a[maxn];
struct Node{
    int sum;int ch[2];
}hjt[maxn*40];
void build(int &p,int cl,int cr){
    if(cl==cr){
        hjt[++cnt].sum=a[cl];
        p=cnt;
        return ;
    }
    hjt[++cnt].sum=0;
    p=cnt;
    int mid{(cl+cr)/2};
    build(hjt[p].ch[0],cl,mid);
    build(hjt[p].ch[1],mid+1,cr);
    hjt[p].sum=hjt[hjt[p].ch[0]].sum+hjt[hjt[p].ch[1]].sum;
    return ;
}
void modify(int pre,int &now,int cl,int cr,int d,int v){
    hjt[++cnt]=hjt[pre];
    now=cnt;
    if(cl==d&&cr==d){
        hjt[now].sum=v;
        return ;
    }
    int mid{(cl+cr)/2};
    if(d<=mid)modify(hjt[pre].ch[0],hjt[now].ch[0],cl,mid,d,v);
    else modify(hjt[pre].ch[1],hjt[now].ch[1],mid+1,cr,d,v);
    hjt[now].sum=hjt[hjt[now].ch[0]].sum+hjt[hjt[now].ch[1]].sum;
    return ;
}
int query(int pre,int cl,int cr,int d){
    if(cl==d&&cr==d){
        return hjt[pre].sum;
    }
    int mid{(cl+cr)/2};
    if(d<=mid)return query(hjt[pre].ch[0],cl,mid,d);
    else return query(hjt[pre].ch[1],mid+1,cr,d);
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    for(int i{1};i<=n;i++)cin>>a[i];
    build(root[0],1,n);
    int v,opt,loc,val;
    for(int i{1};i<=m;i++){
        cin>>v>>opt;
        if(opt==1){
            cin>>loc>>val;
            modify(root[v],root[i],1,n,loc,val);
        }
        if(opt==2){
            cin>>loc;
            cout<<query(root[v],1,n,loc)<<"\n";
            root[i]=root[v];
        }
    }
    cout.flush();
    return 0;
}