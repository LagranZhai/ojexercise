#include<bits/stdc++.h>
constexpr int maxn=5e4;
int main(){
    freopen("e.in","w",stdout);
    srand(time(nullptr));
    std::cout<<maxn<<" "<<rand()%maxn+1<<" "<<rand()%maxn+1<<"\n";
    for(int i{2};i<=maxn;i++){
        std::cout<<i<<" "<<rand()%(i-1)+1<<"\n";
    }
    std::cout.flush();
    return 0;
}