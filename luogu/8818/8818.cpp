#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
int n,m,q;
int l1,l2,r1,r2;
int logn[maxn];
int st1[maxn][18],st2[maxn][18],st3[maxn][18],st4[maxn][18],st5[maxn][18],st6[maxn][18];
void init(){
	logn[0]=0;
	logn[1]=0;
	for(int i=2;i<=max(n,m);i++){
		logn[i]=logn[i/2]+1;
	}
	for(int s=1;s<=logn[n];s++){
		for(int i=1;i+(1<<s)-1<=n;i++){
			st1[i][s]=max(st1[i][s-1],st1[i+(1<<(s-1))-1][s-1]);
			st4[i][s]=min(st4[i][s-1],st4[i+(1<<(s-1))-1][s-1]);
			st2[i][s]=min(st2[i][s-1],st2[i+(1<<(s-1))-1][s-1]);
			st3[i][s]=max(st3[i][s-1],st3[i+(1<<(s-1))-1][s-1]);
		}
	}
	for(int s=1;s<=logn[m];s++){
		for(int i=1;i+(1<<s)-1<=m;i++){
			st5[i][s]=max(st5[i][s-1],st5[i+(1<<(s-1))-1][s-1]);
			st6[i][s]=min(st6[i][s-1],st6[i+(1<<(s-1))-1][s-1]);
		}
	}
}
int query(int l,int r,int st[][18]){
	//int**st=(int**)_st;
	if(st==st1||st==st3||st==st5)return max(st[l][logn[r-l+1]],st[r-(1<<logn[r-l+1])+1][logn[r-l+1]]);
	else return min(st[l][logn[r-l+1]],st[r-(1<<logn[r-l+1])+1][logn[r-l+1]]);
}
long long solve(){
	int q1=query(l1,r1,st1),q2=query(l1,r1,st2),q3=query(l1,r1,st3),q4=query(l1,r1,st4),
		q5=query(l2,r2,st5),q6=query(l2,r2,st6);
	if(q6>=0){
		if(q1>=0)return 1ll*q6*q1;
		if(q1<0)return 1ll*q5*q1;
	}
	else{
		if(q1<0){
			if(q5>=0){
                if(q4>=0)return 1ll*q5*q1;
            }return 1ll*q5*q1;
			if(q5<0)return 1ll*q4*q5;
		}
		else{
			if(q4<0){
				if(q5<0)return 1ll*q5*q4;
				if(q5>=0)
					return max(1LL*q2*q6,1ll*q3*q5);
			}
			if(q4>=0)return 1ll*q4*q6;
		}
	}
}

int main(){
	//freopen("1.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		cin>>st1[i][0];
		st4[i][0]=st1[i][0];
		if(st1[i][0]>=0){
			st2[i][0]=st1[i][0];st3[i][0]=-(1<<30);
		}
		//else if(st1[i][0]==0){
	//		st2[i][0]=st3[i][0]=0;
	//	}
		else{
			st2[i][0]=1<<30;st3[i][0]=st1[i][0];
		}
	}
	for(int i=1;i<=m;i++){
		cin>>st5[i][0];
		st6[i][0]=st5[i][0];
	}
	while(q--){
		cin>>l1>>r1>>l2>>r2;
		cout<<solve()<<'\n';
	}
	//fclose(stdin);
	return 0;
}
