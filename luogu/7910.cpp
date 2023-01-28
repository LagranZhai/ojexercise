#include<bits/stdc++.h>
using namespace std;
const int maxn=10e4;
long long a[maxn];
long long val[maxn];
int fa[maxn],ch[maxn][2],rt,tot,siz[maxn];
inline bool chk(int x){return x==ch[fa[x]][1];}
inline void upsiz(int x){siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;return;}
inline void clean(int x){fa[x]=ch[x][0]=ch[x][1]=siz[x]=0,val[x]=0;return;}
void spin(int x){
	//cout<<"q"<<"\n";
	int f=fa[x],dir=chk(x),ff=fa[f];
	fa[ch[x][dir^1]]=f,ch[f][dir]=ch[x][dir^1];
	if(ff)ch[ff][chk(f)]=x;
	fa[x]=ff,fa[f]=x,ch[x][dir^1]=f;
	upsiz(f),upsiz(x);
	return;
}
void splay(int x){
//	cout<<"w"<<"\n";
	int f=fa[x];
	while(f){
		if(fa[f])spin((chk(x)==chk(f))?f:x);
		spin(x),f=fa[x];
	}
	rt=x;
	return;
}
void insert(long long v){
	//cout<<"e"<<endl;
	if(!rt){
		val[++tot]=v,rt=tot,fa[tot]=0,upsiz(tot);
		return;
	}
	int cur=rt,f=0;
	while(1){
		//cout<<0<<endl;
		bool dir=(v>val[cur]);
		f=cur,cur=ch[cur][dir];
		if(!cur){
			fa[++tot]=f,val[tot]=v,ch[f][dir]=tot,upsiz(tot),upsiz(f);
			splay(tot);
			return;
		}
	}
}
void findx(long long v){
	//cout<<1<<endl;
	int cur=rt,f=0;
	while(1){
		//cout<<7<<endl;
		if(v==val[cur]){
			splay(cur);
			return;
		}
		f=cur,cur=ch[cur][v>val[cur]];
	}
}
int rankx(long long v){
	//cout<<"t"<<"\n";
	findx(v);
	return siz[ch[rt][0]]+1;
}
void del(long long v){
	//cout<<"y"<<endl;
	findx(v);
	//cout<<8<<endl;
	if(!ch[rt][0]&&!ch[rt][1]){
		clean(rt),rt=0;
		return;
	}
	else if(!ch[rt][0]){
		int cur=rt;
		rt=ch[rt][1],fa[rt]=0;
		clean(cur);
		return;
	}
	else if(!ch[rt][1]){
		int cur=rt;
		rt=ch[rt][0],fa[rt]=0;
		clean(cur);
		return;
	}
	else{
		//cout<<9<<endl;
		int cur=ch[rt][0],j=rt;
		while(ch[cur][1]){
			cur=ch[cur][1];
		}
		splay(cur);
		//cout<<10<<endl;
		cur=ch[rt][1]; 
		ch[rt][1]=ch[j][1],fa[ch[j][1]]=rt;
		clean(j),upsiz(rt);
		//cout<<10<<endl;
		return;
	}
}
//int ask(int num,int b){}
int main(){
	//ios::sync_with_stdio(false);
	//freopen("P7910_14.in","r",stdin);
	//freopen("sort.ans","w",stdout);
	int n,q,opt,num,k;
	cin>>n>>q;
	long long ccc=0;
	for(int i=1;i<=n;i++){
		cin>>ccc;
		a[i]=(long long)ccc*10000ll+i;
		insert(a[i]);
		//cout<<a[i]<<" ";
	}
	//cout<<1;
	for(int i=0;i<q;i++){
		scanf("%d",&opt);
		//cout<<i<<endl;
		if(opt==1){
			scanf("%d%d",&num,&k);
			del(a[num]);
			a[num]=(long long)((long long)k*10000ll+num);
			//cout<<num<<" "<<a[num]<<endl;
			insert(a[num]);
		}
		else{
			scanf("%d",&num);
			printf("%d\n",rankx(a[num]));
/*			cin>>num;
			copy(a+1,a+n+1,s);
			sort(s,s+n);
			int mid=(n-1)/2,l=0,r=n-1;
			while(l<=r){
				mid=(r+l)/2;
				if(a[num]==s[mid])break;
				if(a[num]<s[mid]){
					//mid=(l+mid)/2;
					r=mid;
					continue;
				}
				else{
					//mid=(r+mid+1)/2;
					l=mid+1;
					continue;
				}
			}
			cout<<mid+1<<endl;
*/
		}
		//cout<<i<<"\n";
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
