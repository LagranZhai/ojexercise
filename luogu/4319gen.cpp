//P4319gen
#include<bits/stdc++.h>
#include<random>
using std::cin,std::cout,std::ios,std::cerr,std::rand;
// #define int long long
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    freopen("4319.in","w",stdout);
    cout<<50000<<"\n";
    std::srand(std::time(nullptr));
    for(int i{2};i<=50000;i++){
        cout<<i<<" "<<(std::rand()%(i-1)+1)<<" "<<std::rand()<<"\n";
    }
    cout<<32766*3<<"\n";
    int n=5e4;
    for(int i{1};i<=32766*3;i++){
        int a{rand()%32760+1},b{rand()%32760+1};
        if(b<a)std::swap(a,b);
        cout<<rand()%n+1<<" "<<rand()%n+1<<" "<<rand()<<" "<<a<<" "<<b<<"\n";
    }
    cout.flush();
    return 0;
}