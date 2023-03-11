#include<stack>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=8e3;
int a[maxn*2],m[maxn*2]={},n,f[maxn+5][maxn+5]={0},pre[maxn*2],inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=(s<<1+s<<3)+ch-'0';
		ch=getchar();
	}
	return s*f;
}
void write(int x){
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9) 
		write(x/10);
    putchar(x%10+'0');
}
int main(){
	n=read();
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++){
		a[i]=read();
		f[i][1]=pre[i]=max(a[i],pre[i-1]);
	}
	for(int j=2;j<=n;j++){
		stack<int> s,sg,sf;
		s.push(inf);
		sf.push(0);
		sg.push(inf);
		for(int i=1;i<=n;i++){
			int minf=f[i-1][j-1];
			while(!s.empty()&&a[i]>=s.top()){
				minf=min(sf.top(),minf);
				s.pop();sg.pop();
				sf.pop();
			}
			f[i][j]=min(minf+a[i],sg.top());
			s.push(a[i]);
			sf.push(minf);
			sg.push(f[i][j]);		
		}
	}
	for(int i=1;i<=n;i++){
		write(f[n][i]);putchar(' ');
	}
	return 0;
}
