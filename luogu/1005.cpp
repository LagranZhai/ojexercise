#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=80;
int a[maxn+100][maxn+100];
__int128 dp[maxn+100][maxn+100];
int n,m;
void write(__int128 x){
    if(x>=10)write(x/10);
    cout<<int(x%10);
    return ;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            cin>>a[i][j];
        }
    }
    __int128 ans{0};
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            dp[j][j]=2*a[i][j];
        }
        for(int l{2};l<=m;l++){
            for(int j{1};j+l-1<=m;j++){
                dp[j][j+l-1]=std::max(2*dp[j+1][j+l-1]+2*a[i][j],dp[j][j+l-2]*2+2*a[i][j+l-1]);
            }
        }
        ans+=dp[1][m];
    }
    write(ans);
    cout<<std::endl;
    return 0;
}