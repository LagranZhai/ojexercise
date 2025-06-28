//PA
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int ans{0},n,m,t;
    cin>>m>>n;
    for(int i{1};i<=m;i++){
        for(int j{1};j<=n;j++){
            cin>>t;ans+=t;
        }
    }
    cout<<ans<<" 1 1\n";
    if(m==1&&n==1){
        cout<<'u\n';
    }
    else{
        for(int i{1};i<=m;i++){
            if(i%2){
                for(int j{1};j<n;j++){
                    cout<<"r";
                }    
            }
            else{
                for(int j{n};j>1;j--){
                    cout<<"l";
                }    
            }
            if(i!=m)cout<<"d";
        }    
    }
    cout<<"\n";
    cout.flush();
    return 0;
}