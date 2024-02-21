//Pgen
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
signed main(){
    // ios::sync_with_stdio(false);cin.tie(nullptr);
    freopen("B.in","w",stdout);
    cout<<10<<"\n";
    srand(time(nullptr));
    for(int i{1};i<=10;i++){
        int n=(rand()%(int)1e5)+1;
        cout<<n<<" "<<100<<"\n";
        std::set<int> s1,s2;
        while(s1.size()<100){
            s1.insert((rand()%n)+1);
        }
        while(s2.size()<100){
            s2.insert((rand()%n)+1);
        }
        for(int a:s1)cout<<a<<" ";
        cout<<"\n";
        for(int a:s2)cout<<a<<" ";
        cout<<"\n";
    }
    cout.flush();
    return 0;
}