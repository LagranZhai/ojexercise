#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<stack>
#include<vector>
#include<limits>
using std::cin;
using std::ios;
using std::max;
using std::min;
using std::swap;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
        std::forward<T>(_s)
    ){}
    Myos<T>& flush(){
        mys<<std::flush;
        return *this;
    }
    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept{
        mys<<std::forward<Traits>(value);
        return *this;
    }
    ~Myos() {
        flush();
    }
};
template<> Myos<std::ostringstream>& Myos<std::ostringstream>::flush(){
        std::cout<<mys.str()<<std::flush;
        mys.str("");
        return *this;
}
//Myos<std::ostream&> cout{std::cout};
Myos<std::ostringstream> cout{std::ostringstream()};
constexpr int maxn=2e5;
int n,q;
namespace satt{
    //0 compress,1 rake
    constexpr int inf=std::numeric_limits<int >::min();
    constexpr int sup=std::numeric_limits<int >::max();
    int a[maxn+10];
    int ch[maxn+10][3],fa[maxn+10],sum[maxn+10][2],tmin[maxn+10][2],tmax[maxn+10][2],tot=0;
    int add_tag[maxn+10][2],cov_tag[maxn+10][2];
    int siz[maxn+10][2];
    bool rtag[maxn+10];
    std::stack<int > st;
    void init(){
        std::fill(cov_tag[0],cov_tag[0]+2*(maxn+10),inf);
        std::fill(tmin[0],tmin[0]+(maxn+10)*2,sup);
        std::fill(tmax[0],tmax[0]+(maxn+10)*2,inf);
    }
    inline int newnode(){
        if(!st.empty()){
            int t=st.top();
            st.pop();
            return t;
        }
        else return ++tot;
    }
    inline bool isroot(int x){
        return (x!=ch[fa[x]][0])&&(x!=ch[fa[x]][1]);
    }
    inline bool chk(int x){
        return (x==ch[fa[x]][1]);
    }
    //wrong
    inline void clear(int x){
        ch[x][0]=ch[x][1]=ch[x][2]=sum[x][0]=sum[x][1]=a[x]=rtag[x]=fa[x]=0;
        st.push(x);
    }
    inline void setfa(int x,int f,int ch_type){
        if(x)fa[x]=f;
        ch[f][ch_type]=x;
        return ;
    }
    template<const bool ndoe_type> inline void upsum(int x){}
    template<> inline void upsum<1>(int x){
        siz[x][1]=siz[ch[x][0]][1]+siz[ch[x][1]][1]+siz[ch[x][2]][1];
        sum[x][1]=sum[ch[x][0]][1]+sum[ch[x][1]][1]+sum[ch[x][2]][1];
        tmin[x][1]=min(min(tmin[ch[x][0]][1],tmin[ch[x][1]][1]),tmin[ch[x][2]][1]);
        tmax[x][1]=max(max(tmax[ch[x][0]][1],tmax[ch[x][1]][1]),tmax[ch[x][2]][1]);
        return ;
    }
    template<> inline void upsum<0>(int x){
        siz[x][0]=siz[ch[x][0]][0]+siz[ch[x][1]][0]+1;
        sum[x][0]=sum[ch[x][0]][0]+sum[ch[x][1]][0]+a[x];
        tmin[x][0]=min(min(tmin[ch[x][0]][0],tmin[ch[x][1]][0]),a[x]);
        tmax[x][0]=max(max(tmax[ch[x][0]][0],tmax[ch[x][1]][0]),a[x]);
        siz[x][1]=siz[ch[x][0]][1]+siz[ch[x][1]][1]+siz[ch[x][2]][1]+1;
        sum[x][1]=sum[ch[x][0]][1]+sum[ch[x][1]][1]+sum[ch[x][2]][1]+a[x];
        tmin[x][1]=min(min(tmin[ch[x][0]][1],tmin[ch[x][1]][1]),min(a[x],tmin[ch[x][2]][1]));
        tmax[x][1]=max(max(tmax[ch[x][0]][1],tmax[ch[x][1]][1]),max(a[x],tmax[ch[x][2]][1]));
        return ;
    }
    inline void rv(int x){
        if(x){
            rtag[x]^=1;
            swap(ch[x][0],ch[x][1]);
        }
        return ;
    }
    template<const bool node_type,const bool tag_type> inline void modifycovtag(int x,int fa){}
    template<> inline void modifycovtag<0,1>(int x,int tag){
        a[x]=tag;
        sum[x][0]=a[x]*siz[x][0];
        sum[x][1]=a[x]*siz[x][1];
        tmax[x][0]=tmin[x][0]=tmax[x][1]=tmin[x][0]=a[x];
        cov_tag[x][1]=cov_tag[fa][1];
        cov_tag[x][0]=cov_tag[fa][1];
        add_tag[x][0]=0;
        add_tag[x][1]=0;
        return ;
    }
    template<> inline void modifycovtag<1,1>(int x,int fa){
        sum[x][1]=cov_tag[fa][1]*siz[x][1];
        tmin[x][1]=tmax[x][1]=cov_tag[fa][1];
        cov_tag[x][1]=cov_tag[fa][1];
        add_tag[x][1]=0;
        return ;
    }
    template<> inline void modifycovtag<0,0>(int x,int fa){
        a[x]=cov_tag[fa][0];
        sum[x][0]=a[x]*siz[x][0];
        tmax[x][0]=tmin[x][0]=a[x];
        cov_tag[x][0]=cov_tag[fa][1];
        add_tag[x][0]=0;
        return ;
    }
    template<> inline void modifycovtag<1,0>(int x,int fa){
        std::cerr<<"WTF";
        return ;
    }
    template<const bool node_type,const bool tag_type> inline void modifyaddtag(int x,int fa){}
    template<> inline void modifyaddtag<0,1>(int x,int fa){
        a[x]+=add_tag[fa][1];
        sum[x][0]+=siz[x][0]*add_tag[fa][1];sum[x][1]+=siz[x][1]*add_tag[fa][1];
        tmax[x][0]+=add_tag[fa][1];tmax[x][1]+=add_tag[fa][1];
        tmin[x][0]+=add_tag[fa][1];tmin[x][1]+=add_tag[fa][1];
        add_tag[x][1]+=add_tag[fa][1];
        add_tag[x][0]+=add_tag[fa][1];
        return ;
    }
    template<> inline void modifyaddtag<1,1>(int x,int fa){
        sum[x][1]+=add_tag[fa][1]*siz[x][1];
        tmin[x][1]+=add_tag[fa][1];tmax[x][1]+=add_tag[fa][1];
        add_tag[x][1]+=add_tag[fa][1];
        return ;
    }
    template<> inline void modifyaddtag<0,0>(int x,int fa){
        a[x]+=add_tag[fa][1];
        sum[x][0]+=siz[x][0]*add_tag[fa][0];
        tmax[x][0]+=add_tag[fa][0];
        tmin[x][0]+=add_tag[fa][0];
        add_tag[x][0]+=add_tag[fa][0];
        return ;
    }
    template<const bool node_type> inline void pushdown(int x){}
    template<> inline void pushdown<1>(int x){
        if(rtag[x]){
            std::cerr<<"WTF1";
            // rv(ch[x][0]);
            // rv(ch[x][1]);
            // rtag[x]=0;
        }
        if(cov_tag[x][1]!=inf){
            if(ch[x][0])modifycovtag<1,1>(ch[x][0],x);
            if(ch[x][1])modifycovtag<1,1>(ch[x][1],x);
            if(ch[x][2])modifycovtag<0,1>(ch[x][2],x);
            cov_tag[x][1]=inf;
        }
        if(add_tag[x][1]){
            if(ch[x][0])modifyaddtag<1,1>(ch[x][0],x);
            if(ch[x][1])modifyaddtag<1,1>(ch[x][1],x);
            if(ch[x][2])modifyaddtag<0,1>(ch[x][2],x);
            add_tag[x][1]=inf;
        }
        return ;
    }
    template<> inline void pushdown<0>(int x){
        if(rtag[x]){
            rv(ch[x][0]);
            rv(ch[x][1]);
            rtag[x]=0;
        }
        if(cov_tag[x][1]!=inf){
            // if(ch[x][0])modifycovtag<0,1>(ch[x][0],x);
            // if(ch[x][1])modifycovtag<0,1>(ch[x][1],x);
            if(ch[x][2])modifycovtag<1,1>(ch[x][2],x);
            cov_tag[x][1]=inf;
        }
        if(add_tag[x][1]){
            // if(ch[x][0])modifyaddtag<0,1>(ch[x][0],x);
            // if(ch[x][1])modifyaddtag<0,1>(ch[x][1],x);
            if(ch[x][2])modifyaddtag<1,1>(ch[x][2],x);
            add_tag[x][1]=inf;
        }
        if(cov_tag[x][0]!=inf){
            if(ch[x][0])modifycovtag<0,0>(ch[x][0],x);
            if(ch[x][1])modifycovtag<0,0>(ch[x][1],x);
            cov_tag[x][0]=inf;
        }
        if(add_tag[x][0]){
            if(ch[x][0])modifyaddtag<0,0>(ch[x][0],x);
            if(ch[x][1])modifyaddtag<0,0>(ch[x][1],x);
            add_tag[x][0]=0;
        }
        return ;
    }
    template<const bool node_type> inline void reverse_pushdown(int x){
        if(!isroot(x))reverse_pushdown<type >(fa[x]);
        pushdown<type >(x);
    }
    template<const bool node_type> inline void spin(int x){
        int f=fa[x],dir=chk(x),ff=fa[f];
        if(ff)ch[ff][ch[ff][2]==f?2:chk(f)]=x;//?
        if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
        ch[f][dir]=ch[x][dir^1];ch[x][dir^1]=f;
        fa[f]=x;fa[x]=ff;
        upsum<type >(f);upsum<type >(x);
    }
    template<const bool node_type> inline void splay(int x,int goal=0){
        reverse_pushdown<type >(x);
        int f=fa[x];
        while(!isroot(x)&&f!=goal){            
            if(!isroot(f)&&fa[f]!=goal)spin<type >(chk(f)==chk(x)?f:x);
            spin<type >(x);
            f=fa[x];
        }
        // for(int y;y=fa[x],(!isroot(x))&&y!=goal;spin(x,type)){
        //     if(fa[y]!=goal&&(!isroot(y)))spin(chk(x)^chk(y)?x:y,type);
        // }
        return ;
    }
    void del(int x){
        setfa(ch[x][2],fa[x],1);
        if(ch[x][0]){
            int p=ch[x][0];
            pushdown<1 >(p);
            while(ch[p][1]){
                p=ch[p][1];
                pushdown<1 >(p);
            }
            splay<1 >(p,x);
            setfa(ch[x][1],p,1);
            setfa(p,fa[x],2);
            upsum<1 >(p);
            upsum<0 >(fa[x]);
        }
        else setfa(ch[x][1],fa[x],2);
        clear(x);
    }
    void splice(int x){
        splay<1 >(x);
        int y=fa[x];
        splay<0 >(y);
        pushdown<1 >(x);
        if(ch[y][1]){
            swap(fa[ch[x][2]],fa[ch[y][1]]);
            swap(ch[x][2],ch[y][1]);
            upsum<1 >(x);
        }
        else del(x);
        upsum<0 >(ch[y][1]);
        upsum<0 >(y);
    }
    void access(int x){
        splay<0 >(x);
        int cur=x;
        if(ch[x][1]){
            int y=newnode();
            setfa(ch[x][2],y,0);
            setfa(ch[x][1],y,2);
            ch[x][1]=0;
            setfa(y,x,2);
            upsum<1 >(y);
            upsum<0 >(x);
        }
        while(fa[x]){
            splice(fa[x]);
            x=fa[x];
        }
        //splay(cur,0);
        return ;
    }
    void makeroot(int x){
        access(x);
        splay<0 >(x);
        fn(x);
    }
    int findroot(int x){
        access(x);
        splay<0 >(x);
        pushdown<0 >(x);
        while(ch[x][0]){
            x=ch[x][0];
            pushdown<0 >(x);
        }
        splay<0 >(x);
        return x;
    }
    void split(int x,int y){
        makeroot(x);
        access(y);
        splay<0 >(y);
    }
    void cut(int x,int y){
        split(x,y);
        if(ch[y][0]==x&&ch[x][1]==0){
            fa[x]=0;
            ch[y][0]=0;
            upsum<0 >(y);
        }
    }
    void link(int x,int y){
        if(findroot(x)!=findroot(y)){
            access(x);
            makeroot(y);
            setfa(y,x,1);
            upsum<0 >(x);
            upsum<0 >(y);
        }
        return ;
    }
}using namespace satt;
struct edge{
    int u=0,v=0;
}edg[maxn+10];
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    init();
    for(int i{1};i<n;i++){
        cin>>edg[i].u>>edg[i].v;
    } 
    for(int i=1;i<=n;i++){
        cin>>a[i];
        upsum<0>(i);
    }
    for(auto&& [x,y]:edg){
        link(x,y);
    }
    tot=n;
    int opt,x,y;
    for(int i=1;i<=q;i++){
        cin>>opt;
        if(opt==0){
            cin>>x>>y;
            access(x);
            if(ch[x][1]!=0)std::cerr<<"rsexist";
            cov_tag[x][1]=y;

        }
        else if(opt==1){
            link(x,y);
        }
        else if(opt==2){
            cut(x,y);
        }
        else if(opt==3){
            access(x);
            splay<0 >(x);
            a[x]=y;
            upsum<0 >(x);
        }
    }
    cout.flush();
    return 0;
}
