#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=5e5;
#define int long long
int n,k;
int a[maxn*2];
struct Node{
    int ch[2]={0,0};   
    int siz{0};
    int pos{0};
}hjt[maxn*40];//nlogw
int root[maxn*2];
int tot{0};
void update(int oldp,int &p,int pos,int dep){
    p=++tot;
    hjt[p]=hjt[oldp];
    hjt[p].siz+=1;
    if(dep<0){
        hjt[p].pos=pos;
        return ;
    }
    if(((a[pos]>>dep)&1)==0){
        update(hjt[oldp].ch[0],hjt[p].ch[0],pos,dep-1);
        
    }
    else{
        update(hjt[oldp].ch[1],hjt[p].ch[1],pos,dep-1);
    }
}
int query(int oldp,int p,int x,int dep){
    int now{0},oldnow{0};
    if(dep<0){
        if(hjt[p].pos==0)std::cerr<<"w"<<x<<"\n";
        return hjt[p].pos;
    }
    bool dir=(((x>>dep)&1)>0);
    int cnt=hjt[hjt[p].ch[dir^1]].siz-hjt[hjt[oldp].ch[dir^1]].siz;
    if(cnt>0){
        return query(hjt[oldp].ch[dir^1],hjt[p].ch[dir^1],x,dep-1);
        // else return hjt[p].pos;
    }
    else{
        return query(hjt[oldp].ch[dir],hjt[p].ch[dir],x,dep-1);
        // else return hjt[p].pos;
    }
    // std::cerr<<"w";
}
struct Val{
    int l,r,cl,cr,v;
    bool operator<(const Val& a)const{
        return a.v>v;
    }
};
std::priority_queue<Val> q;
signed main(){
    // ios::sync_with_stdio(false);
    freopen("7.in","r",stdin);
    // freopen("")
    cin>>n>>k;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    // update(0,0,0,32);
    for(int i{2};i<=n;i++){
        a[i]=a[i]^a[i-1];
    }
    for(int i{1};i<=n;i++){
        update(root[i-1],root[i],i,32);
        int t=query(0,root[i-1],a[i],32);
        q.push({t,i,1,i-1,(a[t]^a[i])});
        // cout<<(a[t]^a[i])<<std::endl;
    }
    int cnt=0;
    long long ans=0;
    while(k--){
        // ++cnt;
        Val cur=q.top();
        ans+=cur.v;
        q.pop();
        if(cur.cl<cur.l){
            int ca=query(root[cur.cl-1],root[cur.l-1],a[cur.r],32);
            q.push({ca,cur.r,cur.cl,cur.l-1,(a[ca]^a[cur.r])});
            // q.push({cb,cur.r,cur.l+1,cur.cr,a[cb]^a[cur.r]});
        }
        if(cur.l<cur.cr){
            int cb=query(root[cur.l],root[cur.cr],a[cur.r],32);
            q.push({cb,cur.r,cur.l+1,cur.cr,(a[cb]^a[cur.r])});
        }
    }
    cout<<ans<<std::endl;
    return 0;
}