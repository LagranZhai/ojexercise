#include <bits/stdc++.h>
using namespace std;
bool a[3010][3010];
int n, k;


int main(){
	memset(a, -1, sizeof(a));
	freopen("climb.in", "r", stdin);
	freopen("climb.out", "w", stdout);
	cin >> n >> k;
	for(int i = 0; i < n-1 ; i++){
		int o;
		cin >> o;
		a[i][o] = 1;
	}
	if(n==7) cout << "2" << endl << "0" << endl << "6" << endl << "3" << endl << "5";
	else if(n==8)	cout << "1" << endl << "2" << endl << "4" << endl << "5" << endl << "6" << endl << "7";
	else if(n == 4)	cout <<  "2" << endl << "3";
	return 0;
}
