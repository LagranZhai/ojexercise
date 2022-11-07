#include<iostream>
#include<vector>
#include<algorithm>
//#include<cstdio>
using namespace std;
const int maxn=3e5+5;
int n,m,cnt=0;
int a[maxn],root[maxn];
vector<int> b;
struct Node{
    int l,r,sum;
}hjt[maxn*18];
inline int getid(int v){return lower_bound(b.begin(),b.end(),v)-b.begin()+1;}
void update(int cl,int cr,int pre,int &now,int p){
    hjt[++cnt]=hjt[pre];
    now=cnt;
    hjt[now].sum++;
    if(cl==cr)return;
    int mid=(cl+cr)>>1;
    if(p<=mid)update(cl,mid,hjt[pre].l,hjt[now].l,p);
    else if(p>mid)update(mid+1,cr,hjt[pre].r,hjt[now].r,p);
    //return;
}
int query(int cl,int cr,int pre,int now,int k){
    if(cl==cr)return cl;
    int mid=(cl+cr)>>1;
    if(k>hjt[hjt[now].l].sum-hjt[hjt[pre].l].sum){
        k-=hjt[hjt[now].l].sum-hjt[hjt[pre].l].sum;
        return query(mid+1,cr,hjt[pre].r,hjt[now].r,k);
    }
    else return query(cl,mid,hjt[pre].l,hjt[now].l,k);
}
int main(){
    ios::sync_with_stdio(false);
    //cout<<"q";
    cin>>n>>m;
    //cout<<"e";
    for(int i=1;i<=n;i++){
        cin>>a[i];b.push_back(a[i]);
    }
    sort(b.begin(),b.end());
    //cout<<"w";
    b.erase(unique(b.begin(),b.end()),b.end());
    for(int i:b)cout<<i<<' ';
    int nn=b.size()+1;
    //cout<<"nn";
    for(int i=1;i<=n;i++)update(1,n,root[i-1],root[i],getid(a[i]));
    int ll,rr,k;
    while(m--){
        cin>>ll>>rr>>k;
        cout<<b[query(1,n,root[ll-1],root[rr],k)-1]<<'\n';
    }
    return 0;
}
