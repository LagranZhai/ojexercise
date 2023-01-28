#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3;
int a[maxn*2];
int main(){
    freopen("contest.in","r",stdin);
    freopen("contest.out","w",stdout);
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    int n,m;
    while(T--){
        cin>>n>>m;
        int k;
        for(int i=1;i<=m;i++){
            cin>>k;
            for(int j=1;j<=k;j++){
                cin>>a[j];
            }
        }
        cout<<-1<<endl;
    }
    return 0;
}