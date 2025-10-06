#include<bits/stdc++.h>
using std::cin,std::cout;
using ll=long long;
constexpr int maxn = static_cast<int>(1e5);
ll a[maxn+10];

template<typename Datatype,typename Tagtype>
struct SegmentTree{
    std::size_t siz;
    struct Node{
        Datatype d;Tagtype  t;
        Node operator+(const Node& A)const{
            Node res;
            res.d=d+A.d;
            return res;
        }
        void apply(const Tagtype& A,const int len){
            d.apply(A,len);
            t.compose(A);
            return;
        }
    };
    std::vector<Node> tree;

    void pushdown(int p,int l1,int l2){
        tree[p*2].apply(tree[p].t,l1);
        tree[p*2+1].apply(tree[p].t,l2);
        tree[p].t.init();
        return;
    }

    void __build(int p,int cl,int cr,auto& a){
        if(cl==cr){
            tree[p].d.init(a[cl]);
            tree[p].t.init();
            return;
        }
        int mid{(cl+cr)/2};
        __build(p*2,cl,mid,a);__build(p*2+1,mid+1,cr,a);
        tree[p]=tree[p*2]+tree[p*2+1];
        return;
    }

    void __modify(int p,int cl,int cr,const int l,const int r,const Tagtype& k){
        if(cl>=l&&cr<=r){
            tree[p].apply(k,cr-cl+1);
            return;
        }
        int mid{(cl+cr)/2};    
        pushdown(p,mid-cl+1,cr-mid);
        if(l<=mid)__modify(p*2,cl,mid,l,r,k);
        if(r>mid)__modify(p*2+1,mid+1,cr,l,r,k);
        tree[p]=tree[p*2]+tree[p*2+1];
        return;
    }

    void __query(int p,int cl,int cr,const int l,const int r,Datatype& res){
        if(cl>=l&&cr<=r){
            res=res+tree[p].d;
            return;
        }
        int mid{(cl+cr)/2};    
        pushdown(p,mid-cl+1,cr-mid);
        if(l<=mid)__query(p*2,cl,mid,l,r,res);
        if(r>mid)__query(p*2+1,mid+1,cr,l,r,res);
        return;
    }

    SegmentTree(std::size_t s,auto& a):siz(s){
        tree.reserve(4*siz+10);
        __build(1,1,siz,a);
        return;
    }

    void modify(int l,int r,auto& k){
        __modify(1,1,siz,l,r,k);
        return;
    }

    void query(int l,int r,auto& d){
        __query(1,1,siz,l,r,d);
        return;
    }
};



struct Tag{
    ll add;
    Tag(const ll a):add(a){}
    Tag():add(0){}
    void init(){
        add=0;
        return;
    }
    void compose(const Tag& A){
        add+=A.add;
    }
};

struct Data{
    ll sum;
    void init(const ll x){
        sum=x;
        return;
    }
    Data operator+(const Data& A)const{
        Data res;
        res.sum=sum+A.sum;
        return res;
    }
    void apply(const Tag& A,const int len){
        sum+=A.add*len;
        return;
    }

};





int main(){
    std::ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    SegmentTree<Data,Tag> T(n,a);
    int opt,l,r;
    ll d;
    for(int i{};i<m;i++){
        cin>>opt>>l>>r;
        // cout<<"i:"<<i<<" "<<tree[1].d.sum<<std::endl;
        if(opt==1){
            cin>>d;
            Tag t(d);
            T.modify(l,r,t);
        }
        else{
            Data ans{0};
            T.query(l,r,ans);
            cout<<ans.sum<<std::endl;
        }
    }
    return 0;
}