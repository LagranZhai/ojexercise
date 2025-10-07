#include<bits/stdc++.h>
using std::cin;
using std::cout;
int main(){
    int n;
    cin>>n;
    int t{1};
    bool flag{false};
    for(int i{1};i<=n;i++){
        if(t==n)flag=true;
        int a{(n-t)/2};
        for(int j{1};j<=a;j++){
            cout<<" ";
        }
        for(int j{1};j<=t;j++){
            cout<<"*";
        }
        for(int j{1};j<=a;j++){
            cout<<" ";
        }
        cout<<"\n";
        t+=(flag?-1:1)*2;
    }
    cout.flush();
    return 0;
}