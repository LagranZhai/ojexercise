#include<iostream>
#include<vector>
#include<cctype>
#include<cstring>
#define int long long
//#include<queue>
using namespace std;
const int MAXN=1e5+5;
int n,m;
int a[MAXN],fa[MAXN],vis[MAXN];
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
	vis[i]=1;
    if(status[i]==1)return a[i];
    status[i]=2+depth;
    //a[i]=i;
    //int fflag=0;
    for(int j:t[i]){
    	if(vis[j])continue;
    	j=ffind(j);
    	//status[j]=2+depth+1;
        if(status[j]==0){
            //if(finda(j))fflag=1;
            a[i]+=finda(j,depth+1);
            if(fa[j]!=j&&i!=fa[j]){
            	//if(status[ffind(i)]==0||status[ffind(i)]==1)cout<<"whatthefuck";
            	if(status[ffind(i)]<status[ffind(j)]){
            		fa[ffind(j)]=ffind(i);
				}
				else{
					fa[ffind(i)]=ffind(j);
				}
			}
        }
        else if(status[j]==1){
        	//status[j]=2+depth+1;
            a[i]+=a[j];
        }
        else if(status[j]>=2){
            //fflag=1;
            fa[i]=ffind(j);
        }
        vis[j]=1;
    }
//    for(int j:t[i]){
//    	status[j]=1;
//	}
    //if(fflag==0){
    status[i]=1;
    return a[i];
}
signed main(){
    //ios::sync_with_stdio(false);
    cin>>n>>m;
    //init
    for(int i=1;i<=n;i++){
    	fa[i]=i;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
    int ss,ee;
    for(int i=0;i<m;i++){
        cin>>ss>>ee; 
        t[ss].push_back(ee);
    }
    int mmax=0,cur=0;
    for(int i=1;i<=n;i++){
        if(finda(i,0)>mmax){
        	mmax=a[i];
			cur=i;
			mmset(vis,0,n*sizeof(a[0]));
		}
        //putchar(' ');
    }
	printf("%lld %lld",mmax,cur);
    return 0;
}
