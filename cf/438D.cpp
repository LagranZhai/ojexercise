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
#define int long long
int a[maxn*2];
int n,m;
int tree1[maxn*4],tree2[maxn*4];
void merge(auto& a,auto&& b,auto&& c){
    std::get<0>(a)=max(std::get<0>(c),std::get<0>(b));
    std::get<1>(a)=std::get<1>(c)+std::get<1>(b);
    return ;
}
void build(int cl,int cr,int p){
    if(cl==cr){
        tree1[p]=a[cl];
        tree2[p]=a[cl];
        return;
    }
    int mid=(cl+cr)/2;
    build(cl,mid,p*2);
    build(mid+1,cr,p*2+1);
    std::tuple<int&,int& > res{tree1[p],tree2[p]};
    merge(res,
        std::make_tuple(tree1[p*2],tree2[p*2]),
        std::make_tuple(tree1[p*2+1],tree2[p*2+1]));
    return ;
}
struct update{
    int l,d;
    update(int l_,int d_):l(l_),d(d_){}
    void u(int cl,int cr,int p){
        if(cl==cr&&cl==l){
            a[cl]=tree1[p]=tree2[p]=d;
            return ;
        }
        if(cl!=cr){
            int mid=(cl+cr)/2;
            if(l<=mid)u(cl,mid,p*2);
            if(l>mid)u(mid+1,cr,p*2+1);
            std::tuple<int&,int& > res{tree1[p],tree2[p]};
            merge(res,
                std::make_tuple(tree1[p*2],tree2[p*2]),
                std::make_tuple(tree1[p*2+1],tree2[p*2+1]));
        }
    }
    void operator()(int cl,int cr,int p){
        u(cl,cr,p);
    }
};
struct update1{
    int l,r,P;
    update1(int l_,int r_,int P_):l(l_),r(r_),P(P_){}
    void u(int cl,int cr,int p){
        int mid=(cl+cr)/2;
        if((cl>=l&&cr<=r)&&(tree1[p]<P)){
            return ;
        }
        if((cl>=l&&cr<=r)&&(cl==cr)){
            tree1[p]=tree1[p]%P;
            a[cl]=a[cl]%P;
            tree2[p]=tree2[p]%P;
            return ;
        }
        if(cl!=cr){
            if(l<=mid)u(cl,mid,p*2);
            if(r>mid)u(mid+1,cr,p*2+1);
            std::tuple<int&,int& > res{tree1[p],tree2[p]};
            merge(res,
                std::make_tuple(tree1[p*2],tree2[p*2]),
                std::make_tuple(tree1[p*2+1],tree2[p*2+1]));
        }
    }
    void operator()(int cl,int cr,int p){
        u(cl,cr,p);
    }
};
struct query{
    int l,r;
    query(int l_,int r_):l(l_),r(r_){}
    std::tuple<int,int > u(int cl,int cr,int p){
        if(cl>=l&&cr<=r){
            return {tree1[p],tree2[p]};
        }
        std::tuple<int,int > res={0,0};
        if(cl!=cr){
            int mid=(cl+cr)/2;
            if(l<=mid&&r>mid){
                merge(res,u(cl,mid,p*2),u(mid+1,cr,p*2+1));
            }
            else{
                if(l<=mid)return u(cl,mid,p*2);
                if(r>mid)return u(mid+1,cr,p*2+1);
            }
        }
        return res;
    }
    int operator()(int cl,int cr,int p){
        return std::get<1>(u(cl,cr,p));
    }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    build(1,n,1);
{
    int opt,l,r,x;
    for(int i{1};i<=m;i++){
        cin>>opt>>l>>r;
        if(opt==1){
            cout<<query{l,r}(1,n,1)<<"\n";
        }
        if(opt==2){
            cin>>x;
            update1{l,r,x}(1,n,1);
            cout<<"\n";
        }
        if(opt==3){
            update{l,r}(1,n,1);
        }
    }    
}
    cout.flush();
    return 0;
}
