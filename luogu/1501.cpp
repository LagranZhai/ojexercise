#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=2e5,P=51061;
int n,q;
int a[maxn+10],tag1[maxn+10],tag2[maxn+10];
int ch[maxn+10][2],fa[maxn+10],sum[maxn+10],siz[maxn];
bool tag[maxn+10];
inline int chk(int x){
    if(ch[fa[x]][1]==x)return 1;
    if(ch[fa[x]][0]==x)return 0;
    return -1;
}
inline void upsum(int x){
    sum[x]=((sum[ch[x][0]]+sum[ch[x][1]])%P+a[x])%P;
    siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
}
inline void updatetag(int x,int mul,int add){
    sum[x]=(1ll*sum[x]*mul%P+1ll*add*siz[x]%P)%P;
    a[x]=(1ll*a[x]*mul%P+add)%P;
    tag2[x]=1ll*tag2[x]*mul%P;
    tag1[x]=1ll*tag1[x]*mul%P;
    tag1[x]=(0ll+tag1[x]+add)%P;
}
inline void pushdown(int x){
    if(tag[x]){
        swap(ch[x][0],ch[x][1]);
        tag[ch[x][0]]^=1;
        tag[ch[x][1]]^=1;
        tag[x]=0;
    }
    if(ch[x][0]){
        updatetag(ch[x][0],tag2[x],tag1[x]);
    }
    if(ch[x][1]){
        updatetag(ch[x][1],tag2[x],tag1[x]);
    }
    tag1[x]=0;tag2[x]=1;
}
void reverse_pushdown(int x){
    if(chk(x)!=-1)reverse_pushdown(fa[x]);
    pushdown(x);
}
void spin(int x){
    int f=fa[x],dir=chk(x),ff=fa[f];
    if(chk(f)!=-1)ch[ff][chk(f)]=x;
    fa[ch[x][dir^1]]=f;ch[f][dir]=ch[x][dir^1];
    fa[f]=x;ch[x][dir^1]=f;fa[x]=ff;
    upsum(f);upsum(x);
}
void splay(int x){
    reverse_pushdown(x);
    int f=fa[x];
    while(chk(x)!=-1){
        if(chk(f)!=-1)spin(chk(f)==chk(x)?f:x);
        spin(x);
        f=fa[x];
    }
}
void access(int x){
    int son=0;
    while(x){
        splay(x);
        ch[x][1]=son;
        upsum(x);
        son=x;
        x=fa[x];
    }
}
void makeroot(int x){
    access(x);
    splay(x);
    tag[x]^=1;
}
int findroot(int x){
    access(x);
    splay(x);
    int cur=x;
    while(x){
        pushdown(x);
        cur=x;
        x=ch[x][0];
    }
    splay(cur);
    return cur;
}
void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
}
void cut(int x,int y){
    split(x,y);
    if(ch[y][0]==x&&fa[x]==y&&ch[x][1]==0){
        fa[x]=0;
        ch[y][0]=0;
        upsum(y);
    }
}
void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x)fa[x]=y;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    int x,y;
    for(int i=1;i<=n;i++){
        tag2[i]=1;
        a[i]=1;
        //sum[i]=1;
        //siz[i]=1;
    }
    for(int i=1;i<=n-1;i++){
        cin>>x>>y;
        link(x,y);
    }
    char opt;
    int b,c;
    for(int i=1;i<=q;i++){
        cin>>opt;
        //cout<<"b"<<endl;
        if(opt=='+'){
            cin>>x>>y>>b;
            split(x,y);
            updatetag(y,1,b);
            pushdown(y);
            //cout<<"a"<<endl;
        }
        else if(opt=='-'){
            cin>>x>>y>>b>>c;
            cut(x,y);
            link(b,c);
        }
        else if(opt=='*'){
            cin>>x>>y>>b;
            split(x,y);
            updatetag(y,b,0);
            pushdown(y);
        }
        else if(opt=='/'){
            cin>>x>>y;
            split(x,y);
            pushdown(y);
            cout<<sum[y]<<endl;
        }
    }
    return 0;
}
