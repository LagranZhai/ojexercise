#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
const int maxm=2e6+6;
int n,m;
int st[maxn][17];
int logn[maxn];
inline int fr(){
    int w=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')w=w*10+c-'0',c=getchar();
    return w*f;
}
void init(){
    logn[0]=0,logn[1]=0;
    logn[2]=1;
    for(int i=2;i<maxn;i++){
        logn[i]=logn[i/2]+1;
    }
    return;
}
int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    init();
    scanf("%d",&n);
    m=fr();
    for(int i=1;i<=n;i++)st[i][0]=fr();
    for(int s=1;s<=logn[n];s++){
        for(int i=1;i+(1<<s)-1<=n;i++){
            st[i][s]=max(st[i][s-1],st[i+(1<<(s-1))][s-1]);
        }
    }
    int a,b;
    while(m--){
        scanf("%d",&a);
        scanf("%d",&b);
        printf("%d\n",max(st[a][logn[b-a+1]    ],st[b-(1<<logn[b-a+1])+1][logn[b-a+1]]));
    }
    return 0;
}
