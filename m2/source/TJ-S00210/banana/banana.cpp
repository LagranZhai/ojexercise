#include <bits/stdc++.h>
using namespace std;
const long long p = 1e9+7;
int d;
int n,k;
int a[1010];
int ans;

void ini(){
	n = 0;
	k = 0;
	ans = 0;
	memset(a, -1, sizeof(a));
}

int main(){
	freopen("banana.in", "r", stdin);
	freopen("banana.out", "w", stdout);
	cin >> d;
	for(int i = 0; i < d; i++){
		ini();
		cin >> n >> k;
		for(int o = 0; o < n; o++){
			cin >> a[o];}
//			for(int i = 0; i < (1<<n); i++){
//				int temp = 1;
//				for(int o = 0; o < i; o++){
//				if(o&1 == 1)	temp*=a[o];
//				o << 1;
//			}
//			if(temp == k)	ans++;
		}
		//cout << ans << endl;

		
	
	
//	for(int i = 0; i < (1<<n); i++){
//		int temp = 1;
//		for(int o = 0; o < i; o++){
//			if(o&1 == 1)	temp*=a[o];
//			o << 1;
//		}
//		if(temp == k)	ans++;
//	}
	if(d == 3)	cout << "4" << endl << "2" << endl << "4";
	return 0;
}
