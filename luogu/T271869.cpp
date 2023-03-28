#include<iostream>
using namespace std;
int main(){
    int T,n,m;
    cin>>T;
    while(T--){
        cin>>n>>m;
        if(n==1)cout<<1<<endl;
        else cout<<float(n/2.0)<<endl;
    }
    return 0;
}
