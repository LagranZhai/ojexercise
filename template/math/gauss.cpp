//luogu3389
//-std=c++17
#include<vector>
#include<algorithm>
#include<string>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<variant>
using namespace std;
const int maxn=100;
const double eps=1e-12;
int n;
struct Martix{
	int n=0;
	double a[maxn*2][maxn*2]={};
	Martix(int _n):n(_n),a{}{}
	variant<string,vector<double > > gauss(){
		vector<double > ans;
		for(int j=1;j<=n;j++){
			int maxline=j;
			for(int i=j;i<=n;i++){
				if(a[i][j]>a[maxline][j]){
					maxline=i;
				}
			}
			if(fabs(a[maxline][j])<eps){
				return string("No Solution");
			}
			else{
				swap(a[j],a[maxline]);
			}
			double div=a[j][j];
			for(int i=1;i<=n+1;i++){
				a[j][i]=a[j][i]/div;
			}
			for(int i=1;i<=n;i++){
				if(i!=j){
					div=a[i][j]/a[j][j];
					for(int k=1;k<=n+1;k++){
						a[i][k]-=div*a[j][k];
					}
				}
				
			}
			// for(int i=1;i<=n;i++){
			// 	for(int k=1;k<=n+1;k++){
			// 			cout<<a[i][k]<<' ';
			// 		}
			// 		cout<<'\n';
			// }
			
			// cin.get();
		}
		for(int i=1;i<=n;i++){
			ans.push_back(a[i][n+1]);
		}
		return ans;
	}
};
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	Martix c(n);
	double t;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++){
			cin>>t;
			c.a[i][j]=(double)t;
		}
	}
	auto var=c.gauss();
	if(var.index()==0){
		cout<<get<string >(var)<<endl;
	}
	else{
		cout<<setiosflags(ios::fixed);
		for(auto x:get<vector<double > >(var)){
			cout<<setprecision(2)<<x<<endl;
		}
	}
	return 0;
} 
