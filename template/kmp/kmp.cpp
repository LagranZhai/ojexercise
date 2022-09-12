#include<iostream>
#include<cstring>
using namespace std;
const int maxn=10e6+6;
int fail[maxn];
char T[maxn],P[maxn];
string ans;
void getfail(char *P){
	int m=strlen(P);
	fail[0]=-1;
	for(int i=1;i<m;i++){
		int j=fail[i-1];
		while(j>=0&&P[j+1]!=P[i])j=fail[j];
		if(P[j+1]==P[i])j++;
		fail[i]=j;
	}
}
void kmp(char *P,char *T){
	int m=strlen(P);
	int n=strlen(T);
	int j=-1;
	for(int i=0;i<n;i++){
		while(j>=0&&P[j+1]!=T[i])j=fail[j];
		if(P[j+1]==T[i]){
			j++;
			if(j+1==m)cout<<(i-m+2)<<endl;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>T>>P;
	getfail(P);
	kmp(P,T);
	int i=0;
	int l=strlen(P);
	while(i<l){
		cout<<fail[i++]+1<<" "; 
	}
	return 0;
}
