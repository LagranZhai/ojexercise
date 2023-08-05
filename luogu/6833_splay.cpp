#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<set>
#include<limits>
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
Myos<std::ostream&> cout{std::cout};//Myos<std::ostringstream> cout{std::ostringstream()};
constexpr int maxn=1e3;
using ll=long long;
struct Splay{
    int tot=0,rt=0;
    int fa[(maxn+10)*(maxn+10)*2]={},ch[(maxn+10)*(maxn+10)*2][2]={},siz[(maxn+10)*(maxn+10)*2]={},cnt[(maxn+10)*(maxn+10)*2]={};
    std::pair<ll,int > val[(maxn+10)*(maxn+10)*2]={};
    Splay(){
        tot=0;rt=0;
    }
    inline void upsiz(int x){siz[x]=cnt[x]+siz[ch[x][0]]+siz[ch[x][1]];}
    inline bool chk(int x){return x==ch[fa[x]][1];}
    inline void clean(int x){fa[x]=ch[x][0]=ch[x][1]=siz[x]=cnt[x]=0;val[x]=std::make_pair(0,0);}
    void spin(int x){
        int f=fa[x],dir=chk(x),ff=fa[f];
        fa[ch[x][dir^1]]=f,ch[f][dir]=ch[x][dir^1];
        if(ff)ch[ff][chk(f)]=x;
        fa[f]=x,ch[x][dir^1]=f,fa[x]=ff;
        upsiz(f),upsiz(x);
    }
    void splay(int x){
        int f=fa[x];
        while(f){
            if(fa[f])spin((chk(x)==chk(f))?f:x);
            spin(x);
            f=fa[x];
        }
        rt=x;
    }
    void insert(std::pair<ll,int > v){
        if(!rt){
            rt=++tot,fa[tot]=0,cnt[tot]++,val[tot]=v,upsiz(tot);
            return;
        }
        int cur=rt,f=0;
        while(1){
            if(v==val[cur]){
                cnt[cur]++,upsiz(cur),upsiz(f);
                splay(cur);
                return;
            }
            bool dir=(v>val[cur]);
            f=cur,cur=ch[cur][dir];
            if(!cur){
                fa[++tot]=f,cnt[tot]++,ch[f][dir]=tot,val[tot]=v;
                upsiz(tot),upsiz(f);
                splay(tot);
                return;
            }
        }
    }
    int findx(std::pair<ll,int > v){
        if(!rt)return 3;
        int cur=rt,f=0;
        while(1){
            if(v==val[cur]){
                splay(cur);
                return 0;
            }
            bool dir=v>val[cur];
            f=cur,cur=ch[cur][dir];
            if(!cur){
                splay(f);
                return dir+1;
            }
        }
    }
    int rankx(std::pair<ll,int > v){
        int st=findx(v);
        if(st==3)return 1;
        else if(st==0||st==1)return siz[ch[rt][0]]+1;
        else if(st==2)return siz[ch[rt][0]]+cnt[rt]+1;
    }
    int pre(std::pair<ll,int > v){
        int st=findx(v);
        if(st==2)return rt;
        else if(st==3)return 0;
        else{
            int cur=ch[rt][0];
            while(ch[cur][1])cur=ch[cur][1];
            splay(cur);
            return cur;
        }
    }
    void del(std::pair<ll,int > v){
        if(findx(v)!=0)return;
        if(!ch[rt][0]&&!ch[rt][1])clean(rt),rt=0;
        else if(!ch[rt][0]){
            int cur=rt;
            rt=ch[rt][1];
            fa[rt]=0,clean(cur);
        }
        else if(!ch[rt][1]){
            int cur=rt;
            rt=ch[rt][0];
            fa[rt]=0,clean(cur);
        }
        else{
            int cur=rt;
            pre(v);
            fa[ch[cur][1]]=rt,ch[rt][1]=ch[cur][1];
            clean(cur),upsiz(rt);
        }
    }
    std::pair<ll,int > begin(){
        int p=rt;
        while(ch[p][0]){
            p=ch[p][0];
        }
        splay(p);
        return val[rt];
    }
};

int n,m,a,b,c;
ll r[(maxn+10)*(maxn+10)];
bool vis[(maxn+10)*(maxn+10)];
ll dis1[(maxn+10)*(maxn+10)],dis2[(maxn+10)*(maxn+10)],dis3[(maxn+10)*(maxn+10)];
void dijkstra(int s,ll *dis){
    std::fill(dis,dis+(maxn+10)*(maxn+10),std::numeric_limits<ll>::max());
    std::fill(vis,vis+(maxn+10)*(maxn+10),0);
    dis[s]=r[s];
    Splay q{};
    q.insert(std::make_pair(r[s],s));
    auto op=[&](int ord,int p){
        if(!vis[p]){
            q.del(std::make_pair(dis[p],p));
            dis[p]=min(dis[p],dis[ord]+r[p]);
            q.insert(std::make_pair(dis[p],p));
        }
    };
    while(q.rt!=0){
        int cur=(q.begin()).second;
        q.del(q.begin());
        if(!vis[cur]){
            vis[cur]=true;
            if(cur%m!=1){
                op(cur,cur-1);
            }
            if(cur%m!=0){
                op(cur,cur+1);
            }
            if(cur+m<=n*m){
                op(cur,cur+m);
            }
            if(cur-m>0){
                op(cur,cur-m);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n>>m>>a>>b>>c;
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            cin>>r[(i-1)*m+j];
        }
    }
    dijkstra(a,dis1);
    dijkstra((n-1)*m+b,dis2);
    dijkstra((n-1)*m+c,dis3);
    int ansi=0;
    ll ans=std::numeric_limits<ll >::max();
    for(int i{1};i<=n*m;i++){
        if(ans>dis1[i]+dis2[i]+dis3[i]-2*r[i]){
            ans=dis1[i]+dis2[i]+dis3[i]-2*r[i];
            ansi=i;
        }
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}