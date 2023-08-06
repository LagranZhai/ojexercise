#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<stack>
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
int n,m;
namespace satt{
    int a[maxn+10];
    int ch[maxn+10][3],fa[maxn+10],sum[maxn+10][2],tot=0;
    bool tag[maxn+10];
    std::stack<int > st;
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
    inline void clear(int x){
        ch[x][0]=ch[x][1]=ch[x][2]=sum[x][0]=sum[x][1]=a[x]=tag[x]=fa[x]=0;
        st.push(x);
    }
    inline void setfa(int x,int f,int ch_type){
        if(x)fa[x]=f;
        ch[f][ch_type]=x;
        return ;
    }
    template<const bool type > inline void upsum(int x){}
    template<> inline void upsum<1>(int x){
        sum[x][1]=sum[ch[x][0]][1]^sum[ch[x][1]][1]^sum[ch[x][2]][1];
        return ;
    }
    template<> inline void upsum<0>(int x){
        sum[x][0]=sum[ch[x][0]][0]^sum[ch[x][1]][0]^a[x];
        sum[x][1]=sum[ch[x][0]][1]^sum[ch[x][1]][1]^sum[ch[x][2]][1]^a[x];
        return ;
    }
    inline void fn(int x){
        if(x){
            tag[x]^=1;
            swap(ch[x][0],ch[x][1]);
        }
        return ;
    }
    template<const bool type > inline void pushdown(int x){}
    template<> inline void pushdown<1>(int x){
        return;
    }
    template<> inline void pushdown<0>(int x){
        if(tag[x]){
            fn(ch[x][0]);
            fn(ch[x][1]);
            tag[x]=0;
        }
        return ;
    }
    template<const bool type > inline void reverse_pushdown(int x){
        if(!isroot(x))reverse_pushdown<type >(fa[x]);
        pushdown<type >(x);
    }
    template<const bool type > inline void spin(int x){
        int f=fa[x],dir=chk(x),ff=fa[f];
        if(ff)ch[ff][ch[ff][2]==f?2:chk(f)]=x;//?
        if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
        ch[f][dir]=ch[x][dir^1];ch[x][dir^1]=f;
        fa[f]=x;fa[x]=ff;
        upsum<type >(f);upsum<type >(x);
    }
    template<const bool type > inline void splay(int x,int goal=0){
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

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        upsum<0 >(i);
    }
    tot=n;
    int opt,x,y;
    for(int i=1;i<=m;i++){
        cin>>opt>>x>>y;
        if(opt==0){
            split(x,y);
            cout<<sum[y][0]<<"\n";
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