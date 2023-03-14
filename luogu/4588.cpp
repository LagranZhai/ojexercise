#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=1e5;
ll /*a[maxn+100],*/tree[maxn*4+100],q[maxn+100],M;
// void build(int cl,int cr,int p){
//     if(cl==cr){
//         tree[p]=a[cl];
//         return;
//     }
//     int mid=(cl+cr)/2;
//     build(cl,mid,p*2);
//     build(mid+1,cr,p*2+1);
//     tree[p]=tree[p*2]*tree[p*2+1];
// }
void update(int cl,int cr,int p,int l,ll d){
    if(cl==cr&&cl==l){
        tree[p]=d;
        return;
    }
    int mid=(cl+cr)/2;
    if(l<=mid)update(cl,mid,p*2,l,d);
    if(l>mid)update(mid+1,cr,p*2+1,l,d);
    tree[p]=tree[p*2]*tree[p*2+1];
    tree[p]%=M;
}
ll query(int cl,int cr,int p,int l,int r){
    if(cl>cr||l>r)return 1ll;
    if(cl>=l&&cr<=r){
        return tree[p]%M;
    }
    int mid=(cl+cr)/2;
    ll la=1,ra=1;
    if(mid>=l)la=query(cl,mid,p*2,l,r);
    if(mid<r)ra=query(mid+1,cr,p*2+1,l,r);
    return (la*ra)%M;
}
struct Que{
    int opt,pos;
    ll m;
}que[maxn+100];
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    int Q;
    while(t--){
        //fill(a,a+maxn+10,0);
        fill(tree,tree+maxn*4+10,1);
        fill(q,q+maxn+10,0);
        cin>>Q>>M;
        int opt;int pos;ll m;
        int cnt=0;
        for(int i=1;i<=Q;i++){
            cin>>opt;
            que[i].opt=opt;
            if(opt==1){              
                cin>>m;que[i].m=m;
                q[i]=++cnt;
                //update(1,cnt,1,cnt,m);
            }
            if(opt==2){
                cin>>pos;que[i].pos=pos;
                // ll ans=query(1,cnt,1,1,q[pos]-1)*
                //         query(1,cnt,1,);
            }
        }
        //cout<<cnt<<endl;
        int cur=0;
        for(int i=1;i<=Q;i++){
            opt=que[i].opt;
            if(opt==1){              
                m=que[i].m;
                update(1,cnt,1,++cur,m);
                cout<<query(1,cnt,1,1,cur)<<'\n';
            }
            if(opt==2){
                pos=que[i].pos;
                update(1,cnt,1,q[pos],1ll);
                cout<<query(1,cnt,1,1,cur)<<'\n';
            }
        }
    }
    cout.flush();
    return 0;
}