#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
int a,b;
int solve(int a,int b){
    int t=0;
    a=abs(a);b=abs(b);
    t+=min(a,b)*2;
    a=abs(a-b);
    // if(a%2==0){
    //     t+=2*a-1;
    // }
    // else{

    // }
    if(a>0)t+=a*2-1;
    return t;
}
int main(){
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        cin>>a>>b;
        cout<<solve(a,b)<<'\n';
    }
    cout.flush();
    return 0;
}