#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
using std::cin,std::ios,std::max,std::min;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
        std::forward<T>(_s)
    ) {}
    Myos<T>& flush() {
        mys<<std::flush;
        return *this;
    }
    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept {
        mys<<std::forward<Traits>(value);
        return *this;
    }
    ~Myos() {
        flush();
    }
};
template<> Myos<std::ostringstream>& Myos<std::ostringstream>::flush() {
        std::cout<<mys.str()<<std::flush;
        mys.str("");
        return *this;
}
//Myos<std::ostream&> cout{std::cout};
Myos<std::ostringstream> cout{std::ostringstream()};
constexpr int maxn=1e5;
int n,m,q;
struct Segtree {
    int tree[maxn*5],a[maxn*2],tag[maxn*5];
    void build(int cl,int cr,int p) {
        if(cl==cr){
            tree[p]=a[cl];
            tag[p]=0;
            return ;
        }
        int mid=(cl+cr)/2;
        build(cl,mid,p*2);
        build(mid+1,cr,p*2+1);
        tree[p]=tree[p*2]+tree[p*2+1];
        tag[p]=0;
        return ;
    }
    void pushdown(int p,int len){
        if(tag[p]==-1){
            tag[p*2]=-1;
            tag[p*2+1]=-1;
            tree[p*2]=0;
            tree[p*2+1]=0;
            tag[p]=0;
            return ;
        }
        if(tag[p]==1){
            tag[p*2]=1;
            tag[p*2+1]=1;
            tree[p*2]=len-len/2;
            tree[p*2+1]=len/2;
            tag[p]=0;
            return ;
        }
        return ;
    }
    void query(int cl,int cr,int p,int l,int r,int& ans) {
        if(cl>=l&&cr<=r){
            ans+=tree[p];
            return ;
        }
        if(cl<cr){
            pushdown(p,cr-cl+1);
            int mid=(cl+cr)/2;
            if(l<=mid)query(cl,mid,p*2,l,r,ans);
            if(r>mid)query(mid+1,cr,p*2+1,l,r,ans);
            return ;
        }
        return ;
    }
    void update(int cl,int cr,int p,int l,int r,int d) {
        if(cl>=l&&cr<=r){
            tree[p]=d*(int)(cr-cl+1);
            tag[p]=(d==1)?1:-1;
            return ;
        }
        if(cl<cr){
            pushdown(p,cr-cl+1);
            int mid=(cl+cr)/2;
            if(l<=mid)update(cl,mid,p*2,l,r,d);
            if(r>mid)update(mid+1,cr,p*2+1,l,r,d);
            tree[p]=tree[p*2]+tree[p*2+1];
            return ;
        }
        return ;
    }
};
int a[maxn*2],b[maxn*2];
struct Que{
    bool op;
    int l,r;
}que[maxn*2];
bool check(int v){
    Segtree* tree=new Segtree;
    for(int i{1};i<=n;i++){
        if(a[i]>=v)tree->a[i]=1;
        else tree->a[i]=0;
    }
    tree->build(1,n,1);
    for(int i{1};i<=m;i++){
        auto &[op,l,r]=que[i];
        int sum=0;
        tree->query(1,n,1,l,r,sum);
        if(op==1){
            tree->update(1,n,1,l,l+sum-1,1);
            if(l+sum<=r)tree->update(1,n,1,l+sum,r,0);
        }
        else{
            tree->update(1,n,1,r-sum+1,r,1);
            if(r-sum>=l)tree->update(1,n,1,l,r-sum,0);
        }
    }
    int ans=0;tree->query(1,n,1,q,q,ans);
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
    for(int i{1};i<=n;i++)cin>>a[i];
    for(int i{1};i<=m;i++){
        cin>>que[i].op>>que[i].l>>que[i].r;
    }
    std::copy(std::begin(a),std::end(a),std::begin(b));
    std::sort(b+1,b+n+1);
    cin>>q;
    int l=1,r=n,mid=(l+r)/2,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
