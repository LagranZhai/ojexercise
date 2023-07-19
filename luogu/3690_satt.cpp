#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
using std::cin,std::ios,std::max,std::min,std::swap;
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
constexpr int maxn=3e5;
int n,m;
int a[maxn+10];
int ch[maxn+10][3],fa[maxn+10],sum[maxn+10][2],tot=0;
bool tag[maxn+10];
inline int chk(int x){
    if(ch[fa[x]][1]==x)return 1;
    if(ch[fa[x]][0]==x)return 0;
    return -1;
}
inline void clear(int x){
    ch[x][0]=ch[x][1]=ch[x][2]=fa[x]=sum[x][0]=sum[x][1]=a[x]=tag[x]=0;
}
inline void setfa(int x,int f,bool type){
    if(x)fa[x]=f;
    ch[f][type]=x;
    return ;
}
inline void upsum(int x,bool type){
    if(type){
        sum[x][1]=sum[ch[x][0]][1]^sum[ch[x][1]][1]^sum[ch[x][2]][1];
        return ;
    }
    sum[x][0]=sum[ch[x][0]][0]^sum[ch[x][1]][0]^a[x];
    sum[x][1]=sum[ch[x][0]][1]^sum[ch[x][1]][1]^sum[ch[x][2]][1]^a[x];
    return ;
}
inline void fn(int x){
    if(x){
        tag[x]^=1;
        swap(ch[x][0],ch[x][1]);
        return ;
    }
    return ;
}
inline void pushdown(int x,bool type){
    if(type)return ;
    if(tag[x]){
        fn(ch[x][0]);
        fn(ch[x][1]);
        tag[x]=0;
    }
    return ;
}
void reverse_pushdown(int x,bool type){
    if(chk(x)!=-1)reverse_pushdown(fa[x],type);
    pushdown(x,type);
}
void spin(int x,bool type){
    int f=fa[x],dir=chk(x),ff=fa[f];
    if(chk(ff)!=-1)ch[ff][ch[ff][2]==f?2:chk(f)]=x;
    if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
    ch[f][dir]=ch[x][dir^1];ch[x][dir^1]=f;
    fa[f]=x;fa[x]=ff;
    upsum(f,type);upsum(x,type);
}
void splay(int x,bool type,int goal=0){
    reverse_pushdown(x,type);
    int f=fa[x];
    while(chk(x)!=-1&&f!=goal){
        if(chk(f)!=-1&&fa[f]!=goal)spin(chk(f)==chk(x)?f:x,type);
        spin(x,type);
        f=fa[x];
    }
    return ;
}
void del(int x){
    setfa(ch[x][2],fa[x],1);
    if(ch[x][0]){
        int cur=x,rt=x;
        while(x){
            pushdown(x,1);
            cur=x;
            x=ch[x][1];
        }
        splay(cur,1,rt);
        setfa(ch[rt][1],cur,1);
        setfa(cur,fa[rt],2);
        upsum(cur,1);
        upsum(fa[rt],0);
    }
    else setfa(ch[x][1],fa[x],2);
    clear(x);
}
void splice(int x){
    splay(x,1);
    int y=fa[x];
    splay(y,0);
    pushdown(x,1);
    if(ch[y][1]){
        swap(fa[ch[x][2]],fa[ch[y][1]]);
        swap(ch[x][2],ch[y][1]);
        upsum(x,1);
    }
    else del(x);
    upsum(ch[y][1],0);
    upsum(y,0);
}
void access(int x){
    splay(x,0);
    int cur=x;
    if(ch[x][1]){
        int y=++tot;
        setfa(ch[x][2],y,0);
        setfa(ch[x][1],y,2);
        ch[x][1]=0;
        setfa(y,x,2);
        upsum(y,1);
        upsum(x,0);
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
    splay(x,0);
    tag[x]^=1;
    swap(ch[x][0],ch[x][1]);
}
int findroot(int x){
    access(x);
    splay(x,0);
    int cur=x;
    while(x){
        pushdown(x,0);
        cur=x;
        x=ch[x][0];
    }
    splay(cur,0);
    return cur;
}
void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y,0);
}
void cut(int x,int y){
    split(x,y);
    if(ch[y][0]==x&&fa[x]==y&&ch[x][1]==0){
        fa[x]=0;
        ch[y][0]=0;
        upsum(y,0);
    }
}
void link(int x,int y){
    if(findroot(x)!=findroot(y)){
        access(x);
        makeroot(y);
        setfa(y,x,1);
        upsum(x,0);
        upsum(y,0);
    }
    return ;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    tot=n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        upsum(i,0);
    }
    int opt,x,y;
    for(int i=1;i<=m;i++){
        cin>>opt>>x>>y;
        //cout<<"b"<<endl;
        if(opt==0){
            split(x,y);
            cout<<sum[y][0]<<"\n";
            //cout<<"a"<<endl;
        }
        else if(opt==1){
            link(x,y);
        }
        else if(opt==2){
            cut(x,y);
        }
        else if(opt==3){
            access(x);
            splay(x,0);
            a[x]=y;
            upsum(x,0);
        }
    }
    cout.flush();
    return 0;
}