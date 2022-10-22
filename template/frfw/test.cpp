#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int maxn=1e7;
int a1[maxn],b1[maxn];
ll a2[maxn],b2[maxn];
template<typename T>
inline T frc(){
	T w=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')w=w*10+c-'0',c=getchar();
	return f*w;
}
template<typename T>
inline T frcpp(){
	T w=0,f=1;
	char c=cin.get();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=cin.get();
	}
	while(c>='0'&&c<='9')w=w*10+c-'0',c=cin.get();
	return f*w;
}
template<typename T>
void writec(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)writec(x/10);
	putchar(x%10+'0');
	return;
}
template<typename T>
void writecpp(T x){
	if(x<0)cout.put('-'),x=-x;
	if(x>9)writecpp(x/10);
	cout.put(x%10+'0');
	return;
}
int main(){
	freopen("data.txt","w",stdout);
	default_random_engine en1((unsigned)time(nullptr));
	uniform_int_distribution<int> d1;	
	for(int i=0;i<maxn;i++){
		a1[i]=d1(en1);
		writec(a1[i]);
		putchar(' ');
	}
	default_random_engine en2((unsigned)time(nullptr));
	uniform_int_distribution<ll> d2;	
	for(int i=0;i<maxn;i++){
		a2[i]=d1(en2);
		writec(a2[i]);
		putchar(' ');
	}
	fclose(stdout);
	freopen("ans.txt","w",stdout);
	freopen("data.txt","r",stdin);
	time_t s1=clock(),e1;
	for(int i=0;i<maxn;i++){
		cin>>b1[i];
		if(b1[i]!=a1[i]){cout<<"wtf";break;}
	}
	for(int i=0;i<maxn;i++){
		cin>>b2[i];
		if(b2[i]!=a2[i]){cout<<"wtf";break;}
	}
	e1=clock();
	cout<<"cin "<<(double)(e1-s1)/CLOCKS_PER_SEC<<endl;
	fclose(stdin);
	freopen("data.txt","r",stdin);
	time_t s2=clock(),e2;
	for(int i=0;i<maxn;i++){
		scanf("%d",&b1[i]);
		if(b1[i]!=a1[i]){cout<<"wtf";break;}
	}
	for(int i=0;i<maxn;i++){
		scanf("%lld",&b2[i]);
		if(b2[i]!=a2[i]){cout<<"wtf";break;}
	}
	e2=clock();
	cout<<"scanf "<<(double)(e2-s2)/CLOCKS_PER_SEC<<endl;
	fclose(stdin);
	freopen("data.txt","r",stdin);
	time_t s3=clock(),e3;
	for(int i=0;i<maxn;i++){
		b1[i]=frc<int>();
		if(b1[i]!=a1[i]){cout<<"wtf";break;}
	}
	for(int i=0;i<maxn;i++){
		b2[i]=frc<ll>();
		if(b2[i]!=a2[i]){cout<<"wtf";break;}
	}
	e3=clock();
	cout<<"frc "<<(double)(e3-s3)/CLOCKS_PER_SEC<<endl;
	fclose(stdin);
	freopen("data.txt","r",stdin);
	time_t s4=clock(),e4;
	for(int i=0;i<maxn;i++){
		b1[i]=frcpp<int>();
		if(b1[i]!=a1[i]){cout<<"wtf";break;}
	}
	for(int i=0;i<maxn;i++){
		b2[i]=frcpp<ll>();
		if(b2[i]!=a2[i]){cout<<"wtf";break;}
	}
	e4=clock();
	cout<<"frcpp "<<(double)(e4-s4)/CLOCKS_PER_SEC<<endl;
	fclose(stdin);
	freopen("data.txt","r",stdin);
	ios::sync_with_stdio(false); 
	time_t s5=clock(),e5;
	for(int i=0;i<maxn;i++){
		b1[i]=frcpp<int>();
		if(b1[i]!=a1[i]){cout<<"wtf";break;}
	}
	for(int i=0;i<maxn;i++){
		b2[i]=frcpp<ll>();
		if(b2[i]!=a2[i]){cout<<"wtf";break;}
	}
	e5=clock();
	cout<<"frcppfalse "<<(double)(e5-s5)/CLOCKS_PER_SEC<<endl;
	fclose(stdin);
	freopen("data.txt","r",stdin);
	ios::sync_with_stdio(false); 
	time_t s6=clock(),e6;
	for(int i=0;i<maxn;i++){
		cin>>b1[i];
		if(b1[i]!=a1[i]){cout<<"wtf";break;}
	}
	for(int i=0;i<maxn;i++){
		cin>>b2[i];
		if(b2[i]!=a2[i]){cout<<"wtf";break;}
	}
	e6=clock();
	cout<<"cinfalse "<<(double)(e6-s6)/CLOCKS_PER_SEC<<endl;
	fclose(stdin);
	freopen("data.txt","r",stdin);
	ios::sync_with_stdio(false); 
	time_t s7=clock(),e7;
	for(int i=0;i<maxn;i++){
		b1[i]=frc<int>();
		if(b1[i]!=a1[i]){cout<<"wtf";break;}
	}
	for(int i=0;i<maxn;i++){
		b2[i]=frc<ll>();
		if(b2[i]!=a2[i]){cout<<"wtf";break;}
	}
	e7=clock();
	cout<<"frcfalse "<<(double)(e7-s7)/CLOCKS_PER_SEC<<endl;
	fclose(stdin);
	return 0;
}
