#include<bits/stdc++.h>
using namespace std;
long long day,n,k,arr[100007],pos,base;
int main(){
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	cin>>day;
	while(day--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>arr[i];
		}
		pos=0;
		for(int i=1;i<=n;i++){
			base=1;
			for(int j=i;j<=n;j++){
				base*=arr[j];
				if(arr[j]==arr[j-1]){
					j++;pos++;
				}
				if(arr[j]==1) pos++;
				if(base==k){
					pos++;
					break;
				}
			}
		}
		cout<<pos<<"\n";
	}
	return 0;
}
