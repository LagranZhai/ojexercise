<<<<<<< HEAD
#include<iostream>
#include<string.h>
using namespace std;
const int maxn=5010;
int n,type;
long long a[maxn],dp[maxn][maxn],b[maxn][maxn];
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>type;
	if(type==0){
		for(int i=1;i<=n;i++){
			cin>>a[i];
			a[i]+=a[i-1];
		}
	}
	//cout<<"1"<<endl;
	memset(dp,0x7f,sizeof dp);
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>=0;j--){
			long long t=(a[i]-a[j]);
			long long temp=t*t;
			if(j==0){
				dp[i][0]=temp;
			}
			for(int k=j-1;k>=0;k--){
				if(t<b[i][j])break;
				dp[i][j]=dp[j][k]+temp;
				b[i][j]=temp;
			}
		}
	}
	long long ans;
	for(int i=0;i<=n-1;i++){
		ans=min(ans,dp[n][i]);
	}
	cout<<ans;
	return 0;
}
=======
#include<stdio.h>
#include<deque>
#include<string.h>
using namespace std;
using ll =long long;
const int maxn=4e7;
int n,type;
ll a[maxn],tag[maxn],s[maxn];
__int128 dp [maxn];
deque<int> q;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(ll x){
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}
int main(){
	//freopen("1.in","r",stdin);
	n=read();type=read();
	if(type)return 0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		s[i]=s[i-1]+a[i];
	}
    q.push_back(0); 
	for(int i=1;i<=n;i++){
		auto h=++q.begin();
		while(!q.empty()&&!(h==q.end())&&tag[*h]<s[i]){
			q.pop_front();
			h=++q.begin();
		}
		tag[i]=2*s[i]-s[q.front()];
		dp[i]=dp[q.front()]+(s[i]-s[q.front()])*(s[i]-s[q.front()]);
		while(!q.empty()&&tag[q.back()]>tag[i])q.pop_back();
		q.push_back(i);
	}
	write(dp[n]);
	return 0;
}













>>>>>>> new1
