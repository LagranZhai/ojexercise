#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=2e6;
int n,c,m;
struct Que{
    int l,r,i,ans;
    bool operator<(const Que A)const{
        if(r==A.r){
            return l<A.l;
        }
        return r<A.r;
    }
}q[maxn*2];
struct queue{
    int mem[3];
    int* tail{mem};
    int front(){return mem[0];}
    int size(){return tail-mem;}
    void pop(){
        if(size()==2){
            mem[0]=mem[1];
            tail--;
        }
        else if(size()==1){
            mem[0]=0;
            tail--;
        }
    }
    void push(int x){
        *tail=x;
        tail++;
    }
}last[maxn+10];
// int nxt1[maxn*2],nxt2[maxn*2];
int qcnt{0};
int a[maxn*2];
int tree[maxn*2];
inline int lowbit(int x){
    return x&(-x);
}
void modify(int x,int w){
    if(x==0)return ;
    while(x<=n){
        tree[x]+=w;
        x+=lowbit(x);
    }
    return ;
}
int query(int x){
    int ans{0};
    while(x>0){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
void insert(int i){
    if(last[a[i]].size()==2){
        modify(last[a[i]].front(),-1);
        last[a[i]].pop();
    }
    last[a[i]].push(i);
    if(last[a[i]].size()==2){
        modify(last[a[i]].front(),1);
    }
}
// void insert(int i){
//     if(nxt2[a[i]]){
//         modify(nxt2[a[i]],-1);
//     }
//     nxt2[a[i]]=nxt1[a[i]];
//     nxt1[a[i]]=i;
//     if(nxt2[a[i]]){
//         modify(nxt2[a[i]],1);
//     }
// }
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>c>>m;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    for(int i{1};i<=m;i++){
        ++qcnt;
        cin>>q[qcnt].l>>q[qcnt].r;
        q[qcnt].i=i;
    }
    std::sort(q+1,q+qcnt+1);
    int curr{0};
    for(int i{1};i<=m;i++){
        // cout<<q[i].r<<" ";
        while(curr<q[i].r){
            curr++;
            insert(curr);
        }
        q[i].ans=query(q[i].r)-query(q[i].l-1);
    }
    std::sort(q+1,q+qcnt+1,[](const Que &A,const Que &B){return A.i<B.i;});
    for(int i{1};i<=m;i++){
        cout<<q[i].ans<<"\n";
    }
    cout<<std::flush;
    return 0;
}