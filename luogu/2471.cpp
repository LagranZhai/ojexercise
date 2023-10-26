#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=5e4;
int fa[maxn*2],siz[maxn*2],tmax[maxn*2],ch[maxn*2][2],val[maxn*2],date[maxn*2];
int rt{0},tot{0};
void pushup(int x){
    tmax[x]=std::max({val[x],tmax[ch[x][0]],tmax[ch[x][1]]});
    siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
}
bool chk(int x){return x==ch[fa[x]][1];}
void spin(int x){
    int f=fa[x],ff=fa[f],dir=chk(x);
    if(ff)ch[ff][chk(f)]=x;
    fa[x]=ff;fa[f]=x;ch[f][dir]=ch[x][dir^1];
    if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
    ch[x][dir^1]=f;
    pushup(f);pushup(x);
}
void splay(int x,int des=0){
    int f=fa[x];
    while(f!=des){
        if(fa[f]!=des)spin(chk(f)==chk(x)?f:x);
        spin(x);
        f=fa[x];
    }
    if(des==0)rt=x;
}
int insert(int d,int v){
    if(!rt){
        rt=++tot;date[rt]=d;val[rt]=v;pushup(rt);
        return tot;
    }
    int p{rt},f{0},dir{0};
    while(1){
        dir=(d>date[p]);
        f=p;p=ch[p][dir];
        if(!p){
            ch[f][dir]=++tot;fa[tot]=f;
            date[tot]=d;val[tot]=v;
            pushup(tot);pushup(f);
            splay(tot);
            return tot;
        }
    }
}
int find(int d){
    int p{rt},f{0},dir{0};
    while(1){
        if(d==date[p]){
            splay(p);
            return 0;
        }
        dir=(d>date[p]);
        f=p;p=ch[p][dir];
        if(!p){
            splay(f);
            return dir+1;
        }
    }
}
int pre(int d){
    int opt=find(d);
    if(opt==2)return rt;
    else{
        int p{ch[rt][0]};
        while(ch[p][1]){
            p=ch[p][1];
        }
        splay(p);
        return p;
    }
}
int suf(int d){
    int opt=find(d);
    if(opt==1)return rt;
    else{
        int p{ch[rt][1]};
        while(ch[p][0]){
            p=ch[p][0];
        }
        splay(p);
        return p;
    }
}
int expose(int x,int y){
    splay(x);
    splay(y,x);
    return ch[y][chk(y)^1];
}
int n,m;
std::unordered_map<int,int> time_exist;

int main(){
    freopen("2471.in","r",stdin);
    freopen("2471.out","w",stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n;
    int d,v;
    insert(-1e9-1,0);insert(1e9+1,0);
    for(int i{1};i<=n;i++){
        cin>>d>>v;
        time_exist[d]=insert(d,v);
    }
    cin>>m;
    int d1,d2;
    // if(siz[0]>0)std::cerr<<"qidong";
    for(int i{1};i<=m;i++){
        cin>>d1>>d2;
        // cout<<d1<<d2;
        if(time_exist.find(d2)==time_exist.end()){
            if(time_exist.find(d1)==time_exist.end()){
                cout<<"maybe\n";
            }
            else{
                // if(i==144){
                //     // std::cerr<<"w";
                // }
                int p=expose(suf(d2),time_exist[d1]);
                if(tmax[p]>=val[time_exist[d1]]&&siz[p]>0){
                    // if(i==144){
                    //     std::cerr<<"a"<<d1<<" "<<date[pre(date[p])]<<" "<<d2;
                    // }
                    cout<<"false\n";
                }
                else{
                    cout<<"maybe\n";
                }
            }
        }
        else{
            if(time_exist.find(d1)==time_exist.end()){
                int p=expose(time_exist[d2],pre(d1));
                if(tmax[p]>=val[time_exist[d2]]){
                    // if(i==144)std::cerr<<"b";
                    cout<<"false\n";
                }
                else{
                    cout<<"maybe\n";
                }
            }
            else{
                int p=expose(time_exist[d2],time_exist[d1]);
                if(val[time_exist[d1]]>=val[time_exist[d2]]&&val[time_exist[d2]]>tmax[p]){
                    if(siz[p]==d2-d1-1){
                        cout<<"true\n";
                    }
                    else if(siz[p]<d2-d1-1){
                        cout<<"maybe\n";
                    }
                    else{
                        cout<<"wtf\n";
                    }
                }
                else{
                    // if(i==144)std::cerr<<"c";
                    cout<<"false\n";
                }
            }
        }
    }
    cout<<std::flush;
    return 0;
}