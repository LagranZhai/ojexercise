#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,m,end_point[maxn],cnt=0,din[maxn];
vector<int> edg[maxn];
queue<int> q;
__int128 gcd(__int128 a,__int128 b){
	return b>(__int128)0?gcd(b,a%b):a;
}
__int128 rd(){
	__int128 f=1,w=0;
	char c=cin.get();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=cin.get();
	}
	while(c>='0'&&c<='9')w=w*(__int128)10+(__int128)(c-'0'),c=cin.get();
	return w*f;
}
void write(__int128 x){
	if(x<(__int128)0){
		cout.put('-');
		x=-x;
	}
	if(x>(__int128)9)write(x/(__int128)10);
	cout.put(x%(__int128)10+'0');
	return;
} 
struct Frac{
	__int128 p=(__int128)0,q=(__int128)1;
	void yf(){
		__int128 gg=gcd(p,q);
		if(!gg)return; 
		p/=gg;
		q/=gg; 
	}
	Frac(__int128 _p=(__int128)0,__int128 _q=(__int128)1):p(_p),q(_q){yf();}
	Frac add(const Frac &A)const{
		__int128 lcm=this->q/gcd(this->q,A.q)*A.q;
		__int128 a=lcm/this->q,b=lcm/A.q;
		return Frac(this->p*a+b*A.p,lcm);
	}
	Frac times(const Frac &A)const{
		return Frac(this->p*A.p,this->q*A.q);
	}
}v[maxn];
void solve(int p){
	Frac tt=v[p].times(Frac((__int128)1,edg[p].size()));
	for(int to:edg[p]){
		v[to]=v[to].add(tt);
	}
	v[p]=Frac((__int128)0,(__int128)1);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	int num,tmp;
	for(int i=1;i<=n;i++){
		cin>>num;
		if(num==0){
			end_point[++cnt]=i;
		}
		else{
			for(int j=0;j<num;j++){
				cin>>tmp;
				din[tmp]++;
				edg[i].push_back(tmp);
			}
		}
	}
	for(int i=1;i<=m;i++){
		q.push(i);
		v[i]=Frac((__int128)1,(__int128)1);
	}
	while(!q.empty()){
		int fr=q.front();q.pop();
		if(edg[fr].empty()){
			continue;
		}
		solve(fr);
		for(int to:edg[fr]){
			din[to]--;
			if(!din[to])q.push(to);
		}
	}
	for(int i=1;i<=cnt;i++){
		v[end_point[i]].yf();
		write(v[end_point[i]].p);
		cout.put(' ');
		write(v[end_point[i]].q);
		cout.put('\n');
	}
	return 0;
}
