#include<bits/stdc++.h>
#include<variant>
using namespace std;
using v=variant<string,vector<double > >;
const int maxn=100,eps=1e-12;
int n;
struct Martix{
	int n=0;
	double a[maxn*2][maxn*2]={};
	Martix(int _n):n(_n),a{}{}
	v gauss(){
		vector<double > ans;
		for(int j=1;j<=n;j++){
			double maxlinea=0;int maxline=0;
			for(int i=1;i<=n;i++){
				if(a[i][1]>maxlinea){
					maxlinea=a[i][1];
					maxline=i;
				}
			}
			if(maxlinea<eps){
				return "No Solution";
			}
			else{
				swap(a[1],a[maxline]);
			}
			
		}
	}
};
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	Martix c(n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++){
			cin>>c.a[i][j];
		}
	}
	
	return 0;
} 
