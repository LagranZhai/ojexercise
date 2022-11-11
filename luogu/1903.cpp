#include<cstdio>
using namespace std;
const int maxn=133333;
int n,m,cntq=0,cntr=0;
struct Res{
    int p,col;
}opt[maxn];
struct Que{
    int ii,ll,rr;
}q[maxn];
inline int rdch(){
    char c=getchar();
    while(c!='R'&&c!='Q')c=getchar();
    if(c=='R')return 0;
    if(c=='Q')return 1;
}
inline int rd(){
    int w=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')w=w*10+c-'0';
    return w;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)a[i]=rd();
    int typ;
    for(int i=1;i<=m;i++){
        typ=rdch();
        if(typ){
            q[++cntq].ii=i;
            q[cntq].ll=rd();
            q[cntq].rr=rd();
        }
        else{
            cnt
        }
    }
}
