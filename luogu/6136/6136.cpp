#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+6;
int tot=0,rt=0;
int fa[maxn],ch[maxn][2],siz[maxn],cnt[maxn];
long long val[maxn];
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
void splay(int x){
	int f=fa[x];
	while(f){
		if(fa[f])spin((chk(x)==chk(f))?f:x);
		spin(x);
		f=fa[x];
	}
	rt=x;
}
int find_frame(int &cur,int &f,int &dir,
	long long v,function<int(void)> fn1,
	function<int(void)> fn2,function<int(void)> fn3){
	if(!rt)return fn1();
	cur=rt,f=0;
	while(1){
		if(v==val[cur])return fn2();
		dir=(v>val[cur]);
		f=cur,cur=ch[cur][dir];
		if(!cur)return fn3();
	}
}
int insert(int v){
	int cur,f,dir;
	return find_frame(cur,f,dir,v,[&]()->int{
		rt=++tot,fa[tot]=0,cnt[tot]++,val[tot]=v,upsiz(tot);
		return rt;
	},[&]()->int{
		cnt[cur]++,upsiz(cur),upsiz(f);
		splay(cur);
		return cur;
	},[&]()->int{
		fa[++tot]=f,cnt[tot]++,ch[f][dir]=tot,val[tot]=v;
		upsiz(tot),upsiz(f);
		splay(tot);
		return tot;
	});
}
int findx(int v){
	int cur,f,dir;
	return find_frame(cur,f,dir,v,
		[&]()->int{return 3;},
		[&]()->int{splay(cur);return 0;},
		[&]()->int{splay(f);return dir+1;});
}
int rankx(int v){
	int st=findx(v);
	if(st==3)return 1;
	else if(st==0||st==1)return siz[ch[rt][0]]+1;
	else if(st==2)return siz[ch[rt][0]]+cnt[rt]+1;
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
int presuf(int v,bool dir){
	int st=findx(v);
	if(st==2-dir)return rt;
	else if(st==3)return 0;
	else{
		int cur=ch[rt][dir];
		while(ch[cur][1-dir])cur=ch[cur][1-dir];
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
		presuf(v,0);
		fa[ch[cur][1]]=rt,ch[rt][1]=ch[cur][1];
		clean(cur),upsiz(rt);
	}
}
int main(){
	ios::sync_with_stdio(false);
	int n=0,m=0;
	cin>>m>>n;
	int tmp;
	for(int i=1;i<=m;i++){
		cin>>tmp;insert(tmp);
	}
	int opt,x;
	int last=0,ans=0,flag=0;
	int ansq;
	for(int i=0;i<n;i++){
		cin>>opt>>x;
		x^=last;
		if(opt==1)insert(x);
		else if(opt==2)del(x);
		else if(opt==3){
			ansq=rankx(x);
			if(flag==0)ans=ansq,flag=1;
			else ans^=ansq;
			last=ansq;
		}
		else if(opt==4){
			ansq=kth(x);
			if(flag==0)ans=ansq,flag=1;
			else ans^=ansq;
			last=ansq;
		}
		else if(opt==5){
			ansq=val[presuf(x,0)];
			if(flag==0)ans=ansq,flag=1;
			else ans^=ansq;
			last=ansq;
		}
		else if(opt==6){
			ansq=val[presuf(x,1)];
			if(flag==0)ans=ansq,flag=1;
			else ans^=ansq;
			last=ansq;
		}
	}
	cout<<ans<<endl;
	return 0;
}
