//P1368
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=5e5;
int a[maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;
    cin>>n;
    for(int i{};i<n;i++){
        cin>>a[i];
    }
    int i{0},j{1},k{0};
    while(i<n&&j<n&&k<n){
        if(a[(i+k)%n]==a[(j+k)%n])k++;
        else{
            a[(i+k)%n]>a[(j+k)%n]?i+=k+1:j+=k+1;
            k=0;
            if(i==j)i++;
        }
    }
    i=std::min(i,j);
    for(int h{0};h<n;h++){
        cout<<a[(i+h)%n]<<" ";
    }
    cout<<"\n";
    cout.flush();
    return 0;
}