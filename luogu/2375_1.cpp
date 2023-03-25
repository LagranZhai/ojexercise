#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
const int mod=1e9+7;
int n,T;
int nxt[maxn],num[maxn];
long long ans;
char s[maxn];
void getnxt()
{
    for(int i=2,j=0;i<=n;i++)
    {
        while(j&&s[i]!=s[j+1]) j=nxt[j];
        if(s[i]==s[j+1]) j++;
        nxt[i]=j;num[i]=num[j]+1;
    }
}
void getnum()
{
    for(int i=2,j=0;i<=n;i++)
    {
        while(j&&s[i]!=s[j+1]) j=nxt[j];
        if(s[i]==s[j+1])j++;
		//j=nxt[i];
        while((j<<1)>i) j=nxt[j];
        ans=(ans*(long long)(num[j]+1))%mod;
    }
}
int main()
{
	freopen("P2375_2.in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        ans=1;num[1]=1;
        scanf("%s",s+1);n=strlen(s+1);
        getnxt();getnum();
        printf("%lld\n",ans);
    }
    return 0;
}
