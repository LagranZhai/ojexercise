//PB
#include<iostream>
#include<algorithm>
using std::cin;using std::cout;using std::ios;using std::cerr;
// #define int long long
const int maxn=2e5+100,maxk=210,p=1000000007;
int a[maxn],b[maxn];
int c[maxk][maxk];
int fac[maxn],inv[maxn];
int qpow(int x,int y){
    int res{1};
    while(y>0){
        if(y&1)res=1ll*res*x%p;
        x=1ll*x*x%p;
        y>>=1ll;
    }
    return res;
}
int chose(int x,int y){
    if(y<0)return 0;
    return 1ll*fac[x]*inv[y]%p*inv[x-y]%p;
}
// int det(int n){
//     int ans=1,op=0;
//     for(int i{1};i<=n;i++){
//         for(int j{i+1};j<=n;j++){
//             int x{i},y{j};
//             while(c[y][i]){
//                 int t=c[x][i]/c[y][i];
//                 for(int k{i};k<=n;k++)c[x][k]=(0ll+c[x][k]-1ll*c[y][k]*t%p)%p;
//                 std::swap(x,y);
//             }
//             if(x!=i){
//                 // std::swap(c[i],c[x]);
//                 for(int k{1};k<=n;k++){
//                     std::swap(c[x][k],c[i][k]);
//                 }
//                 op^=1;
//             }
//         }
//         if(c[i][i]==0)return 0;
//         else ans=1ll*ans*c[i][i]%p;
//     }
//     if(op)ans=-ans;
//     return (0ll+ans+p)%p;
// }
int det(int n){
    int res{1};bool op{0};
    for(int i{1};i<=n;i++){
        int now{i};
        for(int j{i};j<=n;j++){
            if(c[j][i]){
                now=j;break;
            }
        }
        if(now!=i){
            // std::swap(c[now],c[i]);
            for(int k{1};k<=n;k++)std::swap(c[now][k],c[i][k]);
            op^=1;
        }
        int v{qpow(c[i][i],p-2)};
        for(int j{i+1};j<=n;j++){
            int div{(-1ll*c[j][i]+p)%p*v%p};
            for(int k{i};k<=n;k++){
                c[j][k]=(0ll+c[j][k]+1ll*c[i][k]*div%p)%p;
            }
            // if(c[j][i]!=1ll)cerr<<"w";
        }
    }
    for(int i{1};i<=n;i++){
        res=(1ll*res*c[i][i])%p;
    }
    if(op){
        return p-res;
    }
    else{
        return res;
    }
}
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
signed main(){
    freopen("B.in","r",stdin);
    // ios::sync_with_stdio(false);cin.tie(nullptr);
    int T;cin>>T;
    fac[1]=1;fac[0]=1;
    for(int i{2};i<=maxn-1;i++){
        fac[i]=1ll*fac[i-1]*i%p;
    }
    inv[maxn-1]=qpow(fac[maxn-1],p-2);
    for(int i{maxn-2};i>=1;i--){
        inv[i]=1ll*inv[i+1]*(i+1)%p;
    }
    while(T--){
        int n,k;
        n=read();k=read();
        for(int i{1};i<=k;i++)a[i]=read();
        for(int i{1};i<=k;i++)b[i]=read();
        for(int i{1};i<=k;i++){
            for(int j{1};j<=k;j++){
                if(b[j]<a[i])c[i][j]=0;
                else c[i][j]=chose(n-1+b[j]-a[i],n-1);
            }
        }
        write(det(k));
        puts("\n");
    }
    cout.flush();
    return 0;
}