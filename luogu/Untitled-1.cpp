#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    long long a,b;
    cin>>a>>b;
    long long ans=0;
    while(a!=0||b!=0){
        if(a>0){
            if(b==0){
                ans+=a+1;
                break;
            }
            if(b%2023ll==0){
                a--;b/=2023ll;ans++;
               if(a==0)b++;
            }
            else{
                int t=b%2023ll;
                b-=t;ans+=t;
            }
        }
        else{       
            if(b%2023ll==0){
                b/=2023ll;
                ans++;
            }
            else{
                int t=b%2023ll;
                b-=t;ans+=t;
            }       
        }
    }
    cout<<ans;
    return 0;
}