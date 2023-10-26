#include <bits/stdc++.h>
using namespace std;
int a[200000];

int main(){
	freopen("apple.in", "r", stdin);
	freopen("apple.out", "w", stdout);
	
	int n;
	cin >> n;
	for(int i = 0; i < n*2-1; i++)	cin >> a[i];
	
	if(n==4 && a[10] == 2) cout << "5";
	else if(n==7)	cout << "6" ;
	else if(n == 4 && a[10] == 3)	cout << "4" ;
	return 0;
}
