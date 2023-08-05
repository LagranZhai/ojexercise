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
constexpr int maxn=5e5;
int a[maxn*2],b[maxn*2];
int n,m;
int tree1[maxn*4],tree2[maxn*4],tree3[maxn*4],tree4[maxn*4],tree5[maxn*4];
void merge(auto& a,auto&& b,auto&& c){
    std::get<0>(a)=max(std::get<0>(c),std::get<0>(b));
    std::get<1>(a)=min(std::get<1>(c),std::get<1>(b));
    std::get<2>(a)=std::get<0>(b)-std::get<1>(c);
    std::get<2>(a)=max(std::get<2>(a),max(std::get<2>(c),std::get<2>(b)));
    std::get<3>(a)=std::get<0>(c)-std::get<1>(b);
    std::get<3>(a)=max(std::get<3>(a),max(std::get<3>(c),std::get<3>(b)));
    std::get<4>(a)=max(std::get<2>(b)+std::get<0>(c),std::get<3>(c)+std::get<0>(b));
    std::get<4>(a)=max(std::get<4>(a),max(std::get<4>(b),std::get<4>(c)));
}
void build(int cl,int cr,int p){
    if(cl==cr){
        tree1[p]=a[cl];
        tree2[p]=b[cl];
        tree3[p]=-2e8;
        tree4[p]=-2e8;
        tree5[p]=-2e8;
        return;
    }
    int mid=(cl+cr)/2;
    build(cl,mid,p*2);
    build(mid+1,cr,p*2+1);
    std::tuple<int&,int&,int&,int&,int& > res{tree1[p],tree2[p],tree3[p],tree4[p],tree5[p]};
    merge(res,
        std::tuple{tree1[p*2],tree2[p*2],tree3[p*2],tree4[p*2],tree5[p*2]},
        std::tuple{tree1[p*2+1],tree2[p*2+1],tree3[p*2+1],tree4[p*2+1],tree5[p*2+1]});
    return ;
}
struct update{
    int l,d,t;
    update(int l_,int d_,int t_):l(l_),d(d_),t(t_){}
    void u(int cl,int cr,int p){
        if(cl==cr&&cl==l){
            if(t==1){
                a[l]=d;
                tree1[p]=d; 
            }
            else{
                b[l]=d;
                tree2[p]=d; 
            }
            return ;
        }
        if(cl!=cr){
            int mid=(cl+cr)/2;
            if(l<=mid)u(cl,mid,p*2);
            if(l>mid)u(mid+1,cr,p*2+1);
            std::tuple<int&,int&,int&,int&,int& > res{tree1[p],tree2[p],tree3[p],tree4[p],tree5[p]};
            merge(res,
                std::tuple{tree1[p*2],tree2[p*2],tree3[p*2],tree4[p*2],tree5[p*2]},
                std::tuple{tree1[p*2+1],tree2[p*2+1],tree3[p*2+1],tree4[p*2+1],tree5[p*2+1]});
        }
    }
    void operator()(int cl,int cr,int p){
        u(cl,cr,p);
    }
};
struct query{
    int l,r;
    query(int l_,int r_):l(l_),r(r_){}
    std::tuple<int,int,int,int,int > u(int cl,int cr,int p){
        if(cl>=l&&cr<=r){
            return {tree1[p],tree2[p],tree3[p],tree4[p],tree5[p],};
        }
        std::tuple<int,int,int,int,int > res={-2e8,2e8,-2e8,-2e8,-2e8};
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
        return std::get<4>(u(cl,cr,p));
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    for(int i{1};i<=n;i++){
        cin>>b[i];
    }
    build(1,n,1);  
{
    int opt,l,r;
    for(int i{1};i<=m;i++){
        cin>>opt>>l>>r;
        if(opt==3){
            cout<<query{l,r}(1,n,1)<<"\n";
        }
        else{
            update{l,r,opt}(1,n,1);
        }
    }
}
    cout.flush();
    return 0;
}
