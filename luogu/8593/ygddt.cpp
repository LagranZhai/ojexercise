#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
int n,m,cnt=0;
int x[maxn],y[maxn],v[maxn],a[maxn],p[maxn];
vector<int> h[maxn];
unordered_map<int,int> mp;
long long ans;
template<typename T>
T fr(){
	T w=0,f=1;
	char c=cin.get();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=cin.get();
	}
	while(c>='0'&&c<='9')w=w*10+c-'0',c=cin.get();
	return w*f;
}
int main(){
	freopen("ygddt.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		x[i]=fr<int>();
		y[i]=fr<int>();
		v[i]=fr<int>();
		double t=sqrt(double(2*y[i]/9.8));
		if(mp.find(y[i])==mp.end()){
			mp[y[i]]=++cnt;
			h[cnt].push_back(i);
		}
		else{
			int dx,dv;
			for(int j:h[mp[y[i]]]){
				if(v[i]!=v[j]){
					dx=(x[j]-x[i]),dv=(v[i]-v[j]);
					if(dx==0)continue;
					double mt=(double)dx/dv;
					if(mt>0&&mt<=t){
						p[j]++;p[i]++;
						ans+=2;
					}
				}
			}
			h[mp[y[i]]].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		a[i]=fr<int>();
		//cout<<p[i]<<endl;
		p[i]=min(a[i],p[i]);
	}
	sort(p+1,p+n+1,[](const int &a,const int &b){return a>b;
	});
	for(int i=1;i<=m;i++){
		ans-=p[i];
	}
	cout<<ans<<endl;
	//fclose(stdin);
	return 0;
}
