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
double a[maxn*2];
int n,m;
double tree1[maxn*4];
int tree2[maxn*4];
void merge(int p,int cl,int cr){
    tree1[p]=max(tree1[p*2],tree1[p*2+1]);
    tree2[p]=tree2[p*2];
    int& ans=tree2[p];
    int mid=(cl+cr)/2;
    double lmax=tree1[p*2];
    cl=mid+1;p=p*2+1;
    while(cl<=cr){
        if(tree1[p]<=lmax){
            break;
        }
        mid=(cl+cr)/2;
        if(cl==cr){
            if(tree1[p]>lmax)ans+=1;
            break;
        }
        if(tree1[p*2]<=lmax){
            cl=mid+1;
            p=p*2+1;
        }
        else{
            ans+=tree2[p]-tree2[p*2];
            cr=mid;
            p=p*2;
        }
    }
}
struct update{
    int l;double d;
    update(int l_,double d_):l(l_),d(d_){}
    void u(int cl,int cr,int p){
        if(cl==cr&&cl==l){
            a[l]=d;
            tree1[p]=d;
            tree2[p]=1;
            return ;
        }
        if(cl!=cr){
            int mid=(cl+cr)/2;
            if(l<=mid)u(cl,mid,p*2);
            if(l>mid)u(mid+1,cr,p*2+1);
            merge(p,cl,cr);
        }
    }
    void operator()(int cl,int cr,int p){
        u(cl,cr,p);
    }
};
// struct query{
//     int l,r;
//     query(int l_,int r_):l(l_),r(r_){}
//     std::tuple<double,double > u(int cl,int cr,int p){
//         if(cl>=l&&cr<=r){
//             return {tree1[p],tree2[p]};
//         }
//         std::tuple<double,double > res={0,0};
//         if(cl!=cr){
//             int mid=(cl+cr)/2;
//             if(l<=mid&&r>mid){
//                 merge(res,u(cl,mid,p*2),u(mid+1,cr,p*2+1));
//             }
//             else{
//                 if(l<=mid)return u(cl,mid,p*2);
//                 if(r>mid)return u(mid+1,cr,p*2+1);
//             }
//         }
//         return res;
//     }
//     int operator()(int cl,int cr,int p){
//         return std::get<1>(u(cl,cr,p));
//     }
// };
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m;  
{
    int l;
    double r;
    for(int i{1};i<=m;i++){
        cin>>l>>r;
        update{l,(double)r/(double)l}(1,n,1);
        cout<<tree2[1]<<"\n";
    }
}
    cout.flush();
    return 0;
}
