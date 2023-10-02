//luogu3690
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5;
int n,m;
int a[maxn+10];
int ch[maxn+10][2],fa[maxn+10],sum[maxn+10];
bool tag[maxn+10];
inline int chk(int x){
    if(ch[fa[x]][1]==x)return 1;
    if(ch[fa[x]][0]==x)return 0;
    return -1;
}
inline void upsum(int x){
    sum[x]=sum[ch[x][0]]^sum[ch[x][1]]^a[x];
}
inline void pushdown(int x){
    if(tag[x]){
        swap(ch[x][0],ch[x][1]);
        tag[ch[x][0]]^=1;
        tag[ch[x][1]]^=1;
        tag[x]=0;
    }
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
    splay(x);
    if(fa[x]==0){
        return ;
    }
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
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=a[i];
    }
    int opt,x,y;
    for(int i=1;i<=m;i++){
        cin>>opt>>x>>y;
        //cout<<"b"<<endl;
        if(opt==0){
            split(x,y);
            cout<<sum[y]<<endl;
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
            splay(x);
            a[x]=y;
            upsum(x);
        }
    }
    return 0;
}