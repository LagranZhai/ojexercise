#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
std::string s;
void solve(std::string &s){
    bool f1=1,f2=1;
    char c1,c2='0';
    c1=s[0];
    for(int i{1};i<s.size();i++){
        if(s[i]!=c1){
            f1=0;
            if(c2=='0')c2=s[i];
        }
        if(c2!='0'&&s[i]!=c2&&s[i]!=c1){
            f2=0;
            break;
        }
    }
    if(s.size()>2){
        if(f1)cout<<2<<" "<<4<<"\n";
        else cout<<2<<" "<<2<<"\n";
    }
    else{
        if(s.size()==1){
            cout<<1<<" "<<2<<"\n";
        }
        else{
            if(s[0]!=s[1]){
                cout<<2<<" "<<6<<"\n";
            }
            else{
                cout<<2<<" "<<8<<"\n";
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        cin>>s;
        solve(s);
        cout.flush();  
    }
    cout.flush();
    return 0;
}