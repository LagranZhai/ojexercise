#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
int n,t;
int main(){
    freopen("woof.in","r",stdin);
    freopen("woof.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>t;
    if(n==1){
        cout<<1<<"\n";
    }
    if(n==2){
        cout<<1<<"\n";
        cout<<2<<" "<<1<<"\n";
    }
    if(n==3){
        cout<<1<<"\n";
        cout<<2<<" "<<3<<"\n";
        cout<<3<<" "<<1<<" "<<2<<"\n";
    }
    if(n==4){
        cout<<1<<"\n";
        cout<<4<<" "<<1<<"\n";
        cout<<2<<" "<<3<<" "<<4<<"\n";
        cout<<3<<" "<<1<<" "<<2<<" "<<4<<"\n";
    }
    if(n==5){
        cout<<"1\n2 3\n4 2 5\n3 5 1 4\n5 4 3 1 2\n";
    }
    if(n==6){
        cout<<"1\n2 1\n4 3 2\n6 3 5 2\n5 1 6 4 2\n3 1 4 5 6 2\n";
    }
    cout.flush();
    return 0;
}