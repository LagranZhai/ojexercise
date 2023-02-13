#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
int n,m,cnt=0;
int x[maxn],y[maxn],v[maxn],a[maxn],p[maxn];
vector<int> h[maxn];
double e[maxn];
unordered_map<int,int> mp;
int b[maxn];
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
inline lowbit(int x){return x&-x;}
void add(int i){
    while(i<=n){
        b[i]++;
        i+=lowbit(i);
    }
}
int query(int i){
    int ansq=0;
    while(i>0){
        ansq+=b[i];
        i-=lowbit(i);
    }
    return ansq;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		x[i]=fr<int>();
		y[i]=fr<int>();
		v[i]=fr<int>();
        e[i]=(double)x[i]+(double)v[i]*sqrt(2.0*(double)y[i]/9.8);
		if(mp.find(y[i])==mp.end()){
			mp[y[i]]=++cnt;
			h[cnt].push_back(i);
		}
		else{
			h[mp[y[i]]].push_back(i);
		}
	}
    int cur;
    for(int i=1;i<=cnt;i++){
        cur=h[i].size();
        sort(h[i].begin(),h[i].end(),[](const auto &a,const auto &b){return e[a]>=e[b]};);
        for(int i=0;i<cur;i++){
            add(s[h[i]]);
            p[i]+=query(s[h[i]]-1);
        }
        memset()
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
	fclose(stdin);
	return 0;
}
