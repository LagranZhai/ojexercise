#include<iostream>
using namespace std;
#define int long long
const int MAXN=1e6+5;
int tot=0,rt=0;
int fa[MAXN],ch[MAXN][2],siz[MAXN],cnt[MAXN];
int val[MAXN];
inline void upsiz(int x){siz[x]=cnt[x]+siz[ch[x][0]]+siz[ch[x][1]];}
inline bool chk(int x){return x==ch[fa[x]][1];}
inline void clean(int x){fa[x]=ch[x][0]=ch[x][1]=siz[x]=cnt[x]=val[x]=0;}
void spin(int x){
    int f=fa[x],dir=chk(x),ff=fa[f];
    fa[ch[x][dir^1]]=f,ch[f][dir]=ch[x][dir^1];
    if(ff)ch[ff][chk(f)]=x;
    fa[f]=x,ch[x][dir^1]=f,fa[x]=ff;
    upsiz(f),upsiz(x);
}
void splay(int x,int des=0){
	int f=fa[x];
	while(f!=des){
		if(fa[f]!=des)spin((chk(x)==chk(f))?f:x);
		spin(x);
		f=fa[x];
	}
	if(!des)rt=x;
}
void insert(int v){
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
int findx(int v){
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
int rankx(int v){
	int st=findx(v);
	if(st==3)return 1;
	else if(st==0||st==1)return siz[ch[rt][0]]+1;
	else if(st==2)return siz[ch[rt][0]]+cnt[rt]+1;
}
int pre(int v){
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
int suf(int v){
	int st=findx(v);
	if(st==1)return rt;
	else if(st==3)return 0;
	else{
		int cur=ch[rt][1];
		while(ch[cur][0])cur=ch[cur][0];
		splay(cur);
		return cur;
	}
}
void del(int v){
	findx(v);
	if(cnt[rt]>1){
		cnt[rt]--;
		upsiz(rt);
	}
	else if(!ch[rt][0]&&!ch[rt][1])clean(rt),rt=0;
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
int a[MAXN];
signed main(){
	ios::sync_with_stdio(false);
	int n,q;
	cin>>n>>q;
	int x;
    for(int i{1};i<=n;i++){
        cin>>x;
		a[i]=x;
        insert(x);
    }
    char opt;
	int k;
	insert(0);insert(1e9+2);
	for(int i=0;i<q;i++){
		cin>>opt;
		if(opt=='!'){
			cin>>k>>x;
			del(a[k]);
			a[k]=x;
			insert(a[k]);
		}
		else if(opt=='?'){
			cin>>k>>x;
			int a{rankx(x+1)},b{rankx(k)};
			cout<<a-b<<"\n";
		}
	}
	return 0;
}