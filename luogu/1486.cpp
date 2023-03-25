#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5*4;
int fa[maxn],ch[maxn][2],cnt[maxn],siz[maxn],rt=0,tot=0;
int val[maxn];
bool chk(int x){return ch[fa[x]][1]==x;}
void upsiz(int x){siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+cnt[x];}
void clean(int x){val[x]=siz[x]=cnt[x]=ch[x][0]=ch[x][1]=fa[x]=0;}
void spin(int x){
    int f=fa[x],dir=chk(x),ff=fa[f];
    fa[ch[x][dir^1]]=f;ch[f][dir]=ch[x][dir^1];
    if(ff)ch[ff][chk(f)]=x;
    fa[f]=x;ch[x][dir^1]=f;fa[x]=ff;
    upsiz(f);upsiz(x);
    return;
}
void splay(int x){
    int f=fa[x];
    while(f){
        if(fa[f])spin(chk(f)==chk(x)?f:x);
        spin(x);
        f=fa[x];
    }
    rt=x;
}
void insert(int k){
    if(!rt){
        rt=++tot;fa[rt]=0;cnt[rt]++;val[rt]=k;upsiz(rt);
        return;
    }
    int cur=rt,f=0;
    while(1){
        if(val[cur]==k){
            cnt[cur]++;upsiz(cur);upsiz(f);
            splay(cur);
            return;
        }
        bool dir=(k>val[cur]);
        f=cur;
        cur=ch[cur][dir];
        if(!cur){
            val[++tot]=k;cnt[tot]++;ch[f][dir]=tot;fa[tot]=f;
            upsiz(tot);upsiz(f);
            splay(tot);
            return;
        }
    }
}
int kth(int k){
    int cur=rt;
    while(1){
        if(k<=siz[ch[cur][0]])cur=ch[cur][0];
        else{
            k-=siz[ch[cur][0]]+cnt[cur];
            if(k<=0){
                splay(cur);
                return val[cur];
            }
            cur=ch[cur][1];
        }
    }
}
int findx(int k){
    int cur=rt,f=0;
    while(1){
        if(k==val[cur]){
            splay(cur);
            return 0;
        }
        bool dir=val[cur]<k;
        f=cur;
        cur=ch[cur][dir];
        if(!cur){
            splay(f);
            return dir+1;
        }
    }
}
int split(int k){
    int s=findx(k);
    if(s==0||s==1){
        int d=siz[ch[rt][0]];
        clean(ch[rt][0]);
        ch[rt][0]=0;
        upsiz(rt);
        return d;
    }
    if(s==2){
        int cur=rt;
        int d=siz[ch[rt][0]]+cnt[rt];
        rt=ch[cur][1];
        fa[rt]=0;
        clean(cur);upsiz(rt);
        return d;
    }
}
int main(){
    ios::sync_with_stdio(false);
    int n,min;
    cin>>n>>min;
    char opt;int k;
    int now=0,left=0,delta=0;
    for(int i=1;i<=n;i++){
        cin>>opt>>k;
        if(opt=='I'){
            if(k<min)continue;
            insert(k-delta);now++;
        }
        if(opt=='A'){
            delta+=k;
        }
        if(opt=='S'){
            delta-=k;
            int d=split(min-delta);
            left+=d;now-=d;
        }
        if(opt=='F'){
            int d=split(min-delta);
            left+=d;now-=d;
            if(k>now)cout<<-1<<'\n';
            else cout<<kth(now-k+1)+delta<<'\n';
        }
        //cout<<i<<' '<<opt<<' '<<delta<<' '<<now<<endl;
    }
    cout<<left<<endl;
    return 0;
}