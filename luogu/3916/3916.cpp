#include<iostream>
#include<vector>
#include<cctype>
//#include<queue>
using namespace std;
const int MAXN=1e5+5;
int n,m;
int a[MAXN],fa[MAXN];
inline int read()
{
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}
int ffind(int i){
	return fa[i]=((fa[i]==i)?i:ffind(fa[i]));
}
vector<int> t[MAXN];
int status[MAXN];
int finda(int i,int depth){
	i=ffind(i);
    if(status[i]==1)return a[i];
    status[i]=2+depth;
    a[i]=i;
    //int fflag=0;
    for(int j:t[i]){
    	j=ffind(j);
        if(status[j]==0){
            //if(finda(j))fflag=1;
            a[i]=max(a[i],finda(j,depth+1));
            if(fa[j]!=j&&i!=fa[j]){
            	if(status[ffind(i)]<status[ffind(j)]){
            		fa[ffind(j)]=ffind(i);
				}
				else{
					fa[ffind(i)]=ffind(j);
				}
			}
        }
        else if(status[j]==1){
            a[i]=max(a[i],a[j]);
        }
        else if(status[j]>=2){
            //fflag=1;
            fa[i]=ffind(j);
        }
    }
    //if(fflag==0){
    status[i]=1;
    return a[i];
}
int main(){
    //ios::sync_with_stdio(false);
    n=read();
    m=read();
    //init
    for(int i=1;i<=n;i++){
    	fa[i]=i;
	}
    int ss,ee;
    for(int i=0;i<m;i++){
        ss=read();ee=read();
        t[ss].push_back(ee);
    }
    for(int i=1;i<=n;i++){
        printf("%d ",finda(i,0));
        //putchar(' ');
    }

    return 0;
}
