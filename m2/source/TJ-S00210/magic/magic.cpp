#include <bits/stdc++.h>
using namespace std;
int n;
long long a[1000000]; 
const long long p = 1e9+7;

void ini(){
	a[0] = 1;
	//sum[0] = 1;
	for(int i = 1; i < 1000000-2; i++){
		//a[i] = a[i-1]*3;
		a[i] = (a[i-1]%p)*3;
		//sum[i] = sum[i-1]%p + a[i]%p;
	}
	for(int i = 1; i < 1e6-2; i++){
		//a[i] = a[i-1]*3;
		//a[i] = (a[i-1]%p)*3;
		a[i] = a[i-1]%p + a[i]%p;
	}
}


int main(){
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	cin >> n;
//	int q = clock();
//	cout << "start:" << q << endl;
	ini();
	//for(int i = 0; i < 40; i++)	cout << i <<" " << a[i]%p  <<endl;
	cout << a[n];
	
//	int x = clock();
//	cout << "exit:" << x << endl;
	
	return 0;
}
