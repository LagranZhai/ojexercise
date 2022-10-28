#include<iostream>
#include<vector>
#include<algorithm>
//#include<c_limits>
using namespace std;
using ll=long long;
const int maxn=5e5+5;
ll n,b[maxn];
ll t[maxn],ans;
vector<ll> a;
template<typename T>
inline T fr(){
	T w=0,f=1;
	char c=cin.get();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=cin.get();
	}
	while(c>='0'&&c<='9')w=w*10+c-'0',c=cin.get();
	return w*f;
}
inline int lowbit(int x){return x&-x;}
void add(int i){
	while(i<=n){
		b[i]++;
		i+=lowbit(i);
	}
}
ll query(int i){
    ll ansq=0;
    while(i>0){
        ansq+=b[i];
        i-=lowbit(i);
    }
    return ansq;
}
int main(){
	ios::sync_with_stdio(false);
	n=fr<ll>();
	for(int i=0;i<n;i++){
		t[i]=fr<ll>();
		a.push_back(t[i]);
	}
    a.push_back(0x7f3f7f3f);
	sort(a.begin(),a.end(),[](const ll &a,const ll &b){return a>b;});
	a.erase(unique(a.begin(),a.end()),a.end());
    //for(auto i:a)cout<<i<<" ";
    int te;
	for(int i=0;i<n;i++){
        te=lower_bound(a.begin(),a.end(),t[i],greater<ll>())-a.begin();
        add(te);
        ans+=query(te-1);
    }
    cout<<ans<<endl;
	return 0;
}
