#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=4e4;
int c[maxn*2];
signed main(){
    ios::sync_with_stdio(false);
    int n,a,b,q;
    cin>>n>>a>>b>>q;
    for(int i=1;i<=n;i++)cin>>c[i];
    int x;
    while(q--){
        cin>>x;
        int flag=0;
        for(int i=1;i<=n;i++){
            for(int j=c[i];j<=x;j*=a){
                if((x-j)%b==0){
                    flag=1;break;
                }
            }
            if(flag==1)break;
        }
        if(flag)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}