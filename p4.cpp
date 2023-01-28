#include<bits/stdc++.h>
using namespace std;
void func(string &a,int m,int &ans){
    bool flag=1;
    for(int i=0;i<=m;i++){
        if(a[i]==i+1)flag=0;
    }
    if(flag)ans++;
}
void permutation(string &a, int k, int m, int depth, int &ans){
	if (k == m){
        if(depth%2==0){
            func(a,m,ans);
        }
	}
	else{
        permutation(a,k+1,m,depth,ans);
		for (int j = k + 1; j <= m; j++){
			swap(a[j], a[k]);
			permutation(a, k + 1, m, depth + 1, ans);
			swap(a[j], a[k]);
		}
	}
}
int main(){
    int n=100;
    for(int i=1;i<=n;i++){
        string a;
        int ans=0;
        for(int i=0;i<n;i++)a[i]=i+1;
        permutation(a,0,i-1,0,ans);
        cout<<ans<<endl;
    }
}