#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("turing.in","r",stdin);
    freopen("turing.out","w",stdout);
    int n,n1,n2;
    cin>>n>>n1>>n2;
    int a1,a2,a3,a4,a5,a6;
    cin>>a1>>a2>>a3>>a4>>a5>>a6;
    if(a2==a4){
        cout<<"next"<<endl<<a1<<" "<<a5<<" "<<a3*a6;
    }
    else{
        cout<<0;
    }
}