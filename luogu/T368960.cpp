#include<iostream>
#include<algorithm>
using std::cin,std::cout,std::ios;
int main(){
    ios::sync_with_stdio(false);
    int n,m,x,p;
    cin>>n>>m>>x>>p;
    int t=0,maxa=0;
    for(int i{1};i<=n;i++){
        cin>>t;
        maxa=std::max(maxa,t);
    }
    if(maxa<=m){
        cout<<0<<"\n";
    }
    else{
        if((maxa-m)%x==0){
            cout<<(maxa-m)/x<<"\n";
        }
        else{
            cout<<(maxa-m)/x+1<<"\n";
        }    
    }
    
    return 0;
}