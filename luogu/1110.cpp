#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
constexpr int maxn=1e6,omaxn=5e5;
int n,m;
struct valsplay{
    int fa[maxn+100],ch[maxn+100][2],val[maxn+100],siz[maxn+100],cnt[maxn+100];
    int tot{0},rt{0};
    std::stack<int> mem{};
    int chk(int x){
        return x==ch[fa[x]][1];
    }
    void clear(int x){
        fa[x]=ch[x][0]=ch[x][1]=val[x]=siz[x]=cnt[x]=0;
        mem.push(x);
    }
    int newnode(){
        if(mem.empty()){
            ++tot;
            return tot;
        }
        else{
            int x{mem.top()};
            mem.pop();
            return x;
        }
    }
    void pushup(int x){
        siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+cnt[x];
    }
    void spin(int x){
        int f{fa[x]},ff{fa[f]},dir{chk(x)};
        if(ff)ch[ff][chk(f)]=x;
        fa[x]=ff;fa[f]=x;ch[f][dir]=ch[x][dir^1];
        if(ch[x][dir^1])fa[ch[x][dir^1]]=f;
        ch[x][dir^1]=f;
        pushup(f);pushup(x);
    }
    void splay(int x,int des=0){
        int f{fa[x]};
        while(f!=des){
            if(fa[f]!=des)spin((chk(f)==chk(x))?f:x);
            spin(x);
            f=fa[x];
        }
        if(des==0)rt=x;
    }
    int ins(int v){
        if(rt==0){
            rt=newnode();
            cnt[rt]=1;val[rt]=v;
            pushup(rt);
            return 0;
        }
        int x{rt},f{0},dir{0};
        while(1){
            if(val[x]==v){
                cnt[x]++;pushup(x);pushup(f);
                splay(x);
                return 1;
            }
            dir=(v>val[x]);
            f=x;x=ch[x][dir];
            if(x==0){
                x=newnode();
                ch[f][dir]=x;fa[x]=f;cnt[x]++;val[x]=v;pushup(x);pushup(f);
                splay(x);return 0;
            }
        }
    }
    int findbyv(int v){
        if(rt==0)return 3;
        int x{rt},f{0},dir{0};
        while(1){
            if(v==val[x]){
                splay(x);
                return 0;
            }
            dir=(v>val[x]);
            f=x;x=ch[x][dir];
            if(x==0){
                splay(f);
                return dir+1;
            }
        }
    }
    int pre(int v){
        int opt{findbyv(v)};
        if(opt==2)return val[rt];
        else{
            int x{ch[rt][0]};
            if(x==0)return -1;
            while(ch[x][1])x=ch[x][1];
            splay(x);
            return val[x];
        }
    }
    int suf(int v){
        int opt{findbyv(v)};
        if(opt==1)return val[rt];
        else{
            int x{ch[rt][1]};
            if(x==0)return -1;
            while(ch[x][0])x=ch[x][0];
            splay(x);
            return val[x];
        }
    }
    int del(int v){
        int opt{findbyv(v)};
        if(opt!=0){
            return -1;
        }
        if(cnt[rt]>1){
            cnt[rt]--;
            pushup(rt);
            return 0;
        }
        if(ch[rt][0]==0&&ch[rt][1]==0){
            clear(rt);
            rt=0;
            return 0;
        }
        else if(ch[rt][0]==0){
            fa[ch[rt][1]]=0;
            int cur{rt};
            rt=ch[rt][1];
            clear(cur);
            return 0;
        }
        else if(ch[rt][1]==0){
            fa[ch[rt][0]]=0;
            int cur{rt};
            rt=ch[rt][0];
            clear(cur);
            return 0;
        }
        else{
            int cur{rt};
            pre(val[rt]);
            ch[rt][1]=ch[cur][1];fa[ch[cur][1]]=rt;
            pushup(rt);
            clear(cur);
            return 0;
        }
    }
    int getmin(){
        int x{rt};
        while(ch[x][0])x=ch[x][0];
        splay(x);
        return val[x];
    }
}s1,s2;
std::vector<int> seq[omaxn+10];
int minsortgap{std::numeric_limits<int>::max()};
int samecnt{0};
void inss1(int v){
    if(s1.ins(v))samecnt++;
    if(samecnt==0){
        int dv{s1.pre(v)};
        if(dv!=-1){
            minsortgap=std::min(minsortgap,std::abs(dv-v));
        }
        dv=s1.suf(v);
        if(dv!=-1){
            minsortgap=std::min(minsortgap,std::abs(dv-v));
        }
    }
    else{
        minsortgap=0;
    }
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int t,k;
    std::string p;
    for(int i{1};i<=n;i++){
        cin>>t;
        seq[i].push_back(t);
        inss1(t);
        if(i>=2){
            s2.ins(std::abs(seq[i][0]-seq[i-1][0]));
        }
    }
    for(int i{1};i<=m;i++){
        cin>>p;
        if(p=="INSERT"){
            cin>>t>>k;
            if(t!=n){
                s2.del(std::abs(seq[t].back()-seq[t+1].front()));
            }
            s2.ins(std::abs(k-seq[t+1].front()));
            s2.ins(std::abs(k-seq[t].back()));
            seq[t].push_back(k);
            inss1(k);
        }
        else if(p=="MIN_SORT_GAP"){
            cout<<minsortgap<<"\n";
        }
        else if(p=="MIN_GAP"){
            cout<<s2.getmin()<<"\n";
        }
    }
    // cerr<<rt;
    // dfs(rt);
    cout<<std::endl;
    cout<<std::flush;
    return 0;
}