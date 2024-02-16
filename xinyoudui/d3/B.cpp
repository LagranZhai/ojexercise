//PB
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int maxn=100;
int h[maxn][maxn];
char ans[maxn*6][maxn*6];
int n,m;
void print(int x,int y){
    auto p1=[](int x,int y){
        ans[x][y]='+';
        ans[x][y+1]='-';ans[x][y+2]='-';ans[x][y+3]='-';
        ans[x][y+4]='+';
    };
    p1(x,y);p1(x-3,y);p1(x-5,y+2);
    ans[x-2][y+6]='+';
    auto p2=[](int x,int y){
        ans[x-1][y]='|';ans[x-2][y]='|';
    };
    p2(x,y);p2(x,y+4);p2(x-2,y+6);
    ans[x-1][y+5]='/';ans[x-4][y+1]='/';ans[x-4][y+5]='/';
    ans[x-1][y+1]=' ';ans[x-1][y+2]=' ';ans[x-1][y+3]=' ';
    ans[x-2][y+1]=' ';ans[x-2][y+2]=' ';ans[x-2][y+3]=' ';
    ans[x-4][y+2]=' ';ans[x-4][y+3]=' ';ans[x-4][y+4]=' ';
    ans[x-2][y+5]=' ';ans[x-3][y+5]=' ';
}
int hm[maxn];
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>m;
    int k{0},l;
    for(int i{1};i<=n;i++){
        int x{0};
        for(int j{1};j<=m;j++){
            cin>>h[i][j];
            x=std::max(x,h[i][j]);
            hm[i]=x;
        }
        k=std::max(k,(n-i)*2+3+x*3);
    }
    l=4*m+1+2*n;
    for(int i{1};i<=k;i++){
        for(int j{1};j<=l;j++){
            ans[i][j]='.';
        }
    }
    int x{6},y{1};
    for(int i{1};i<=n;i++){
        for(int j{1};j<=m;j++){
            x=k-(n-i)*2;y=2*(n-i)+1+4*(j-1);
            for(int k{1};k<=h[i][j];k++){
                print(x,y);
                x-=3;
            }
        }
    }
    for(int i{1};i<=k;i++){
        for(int j{1};j<=l;j++){
            cout<<ans[i][j];
        }
        cout<<"\n";
    }
    cout.flush();
    return 0;
}