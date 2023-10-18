#include<iostream>
#include<algorithm>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int maxn=2e3;
int a[maxn+100][maxn+100];
int b[maxn+100][maxn+100];
void init(int k){
    for(int i{0};i<=maxn;i++)a[i][0]=1;
    for(int i{1};i<=maxn;i++){
        for(int j{1};j<=i;j++){
            a[i][j]=(a[i-1][j-1]+a[i-1][j])%k;
            if(!a[i][j])b[i][j]=1;
        }
    }
    for(int i{1};i<=maxn;i++){
        for(int j{1};j<=maxn;j++){
            b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    int t,k;
    cin>>t>>k;
    int n,m;
    init(k);
    while(t--){
        cin>>n>>m;
        cout<<b[n][m]<<"\n";
    }
    return 0;
}