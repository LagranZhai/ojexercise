#include<bits/stdc++.h>
#define ls(x) T[x][0]
#define rs(x) T[x][1]
#define ms(x) T[x][2]
#define maxn 200005
using namespace std;
int read(){
    int s=0;
    char a=getchar();
    while(!isdigit(a))a=getchar();
    while(isdigit(a)){
        s=(s<<1)+(s<<3);
        s+=a^48;
        a=getchar();
    }
    return s;
}
int T[maxn][3],s[maxn][2],tot,v[maxn],n,m,r[maxn],top,st[maxn],f[maxn];
int nnd(){
    if(top){top--;return st[top+1];}
    else return ++tot; 
}
bool isr(int x){return rs(f[x])!=x&&ls(f[x])!=x;}
bool dir(int x){return rs(f[x])==x;} 
void upsum(int x,int ty){
    if(ty){
        s[x][1]=s[ls(x)][1]^s[rs(x)][1]^s[ms(x)][1];return;
    }
    s[x][0]=s[ls(x)][0]^v[x]^s[rs(x)][0];
    s[x][1]=s[ls(x)][1]^s[ms(x)][1]^s[rs(x)][1]^v[x];
}
void psr(int x){if(!x)return;r[x]^=1;swap(ls(x),rs(x));}
void pushdown(int x,int ty){
    if(ty)return;
    if(r[x]){psr(ls(x));psr(rs(x));r[x]=0;return;}
}
void upd(int x,int ty){if(!isr(x))upd(f[x],ty);pushdown(x,ty); } 
void stf(int x,int fa,int ty){if(x)f[x]=fa;T[fa][ty]=x;return;}
void rtt(int x,int ty){
    int y=f[x],z=f[y],d=dir(x),w=T[x][d^1];
    if(z)T[z][ms(z)==y?2:dir(y)]=x;
    T[x][d^1]=y;T[y][d]=w;
    if(w)f[w]=y;f[y]=x;f[x]=z;
    upsum(y,ty);upsum(x,ty);
}
void spy(int x,int ty,int gl=0){
    upd(x,ty);for(int y;y=f[x],(!isr(x))&&y!=gl;rtt(x,ty)){
        if(f[y]!=gl&&(!isr(y)))rtt(dir(x)^dir(y)?x:y,ty);
    }
} 
void cle(int x){ls(x)=ms(x)=rs(x)=s[x][0]=s[x][1]=r[x]=v[x]=0;st[++top]=x; }
void del(int x){
    stf(ms(x),f[x],1);
    if(ls(x)){
        int p=ls(x);pushdown(p,1);while(rs(p))p=rs(p),pushdown(p,1);
        spy(p,1,x);stf(rs(x),p,1);stf(p,f[x],2);upsum(p,1);upsum(f[x],0); 
    }
    else stf(rs(x),f[x],2);cle(x);
}
void spl(int x){
    spy(x,1);int y=f[x];spy(y,0);pushdown(x,1);
    if(rs(y)){
        swap(f[ms(x)],f[rs(y)]);swap(ms(x),rs(y));upsum(x,1);
    }
    else del(x);
    upsum(rs(y),0);upsum(y,0);
}
void acs(int x){
    spy(x,0);int ys=x;if(rs(x)){
        int y=nnd();stf(ms(x),y,0);stf(rs(x),y,2);
        rs(x)=0;stf(y,x,2);upsum(y,1);upsum(x,0);
    }
    while(f[x]){spl(f[x]);x=f[x];}spy(ys,0);
}
int fdr(int x){
    acs(x);pushdown(x,0);while(ls(x))x=ls(x),pushdown(x,0);spy(x,0);return x;
}
void mkr(int x){acs(x);psr(x);}
void epo(int x,int y){mkr(x);acs(y);}
void lnk(int x,int y){
    if(fdr(x)==fdr(y))return;
    acs(x);mkr(y);stf(y,x,1);
    upsum(x,0);upsum(y,0);
}
void cu(int x,int y){
    epo(x,y);if(ls(y)!=x||rs(x))return;
    f[x]=ls(y)=0;upsum(y,0);
}
int main(){
    int i,j,op,U,V,n=read(),m=read();tot=n;
    for(i=1;i<=n;i++)v[i]=read(),upsum(i,0);
    for(i=1;i<=m;i++){
        op=read();U=read();V=read();
        if(op==0){epo(U,V);cout<<s[V][0]<<'\n';}
        if(op==1)lnk(U,V);
        if(op==2)cu(U,V);
        if(op==3){acs(U);v[U]=V;upsum(U,0);} 
    }
    return 0;
}