#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=5;
std::string s[maxn*2];
bool checkl(int a,int b){
    if(a<=2){
        if((s[a+1][b]=='o')&&s[a+2][b]=='o'&&s[a+3][b]=='o'){
            return true;
        }
    }
    if(b<=2){
        if(s[a][b]=='o'&&s[a][b+1]=='o'&&s[a][b+2]=='o'){
            return true;
        }
    }
    return false;
}
bool checks(int a,int b){
    if(a<=4&&b<=4){
        if(s[a][b]=='o'&&s[a+1][b-1]=='o'&&s[a+1][b]=='o'){
            return true;
        }
    }
    return false;
}
// bool checkz(int a,int b){
//     if(a<=4&&b<=3){
//         if(s[a][b]=='o'&&s[a+1][b]=='o'&&s[a+1][b+1]=='o'){
//             return true;
//         }
//     }
//     if(a<=3&&b<=4){
//         if()
//     }
// }
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--){
        for(int i{1};i<=5;i++){
            cin>>s[i];
        }
        int c{0};
        int a,b;bool flag{0};
        for(int i{1};i<=5;i++){
            for(int j{0};j<5;j++){
                if(s[i][j]=='o'){
                    c++;
                    if(!flag){
                        a=i;b=j+1;
                        flag=1;
                    }
                }
            }
        }
        if(c==1){
            cout<<"Away"<<"\n";
        }
        else if(c==2){
            cout<<"Far"<<"\n";
        }
        else if(c==3){
            cout<<"Away"<<"\n";
        }
        else{
            if(checkl(a,b)||checks(a,b)){
                cout<<"Away"<<"\n";
            }
            else{
                cout<<"Far"<<"\n";
            }
        }
    }
    cout.flush();
    return 0;
}