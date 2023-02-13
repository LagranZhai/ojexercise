#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> v;
int main(){
    int a,b,t;
    cin>>a>>b;
    for(int i=1;i<=a;i++){
        for(int j=1;j<=b;j++){
            cin>>t;
            v[i][j]=(t);
        }
    }
    cout<<1<<endl;
    cout.flush();
    return 0;
}