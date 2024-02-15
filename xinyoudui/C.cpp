//PC
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
#define int long long
constexpr int p=1e9+7;
struct Matrix{
    int a[3][3]{{{}}};
    int n,m;
    Matrix(int _n=0,int _m=0):n(_n),m(_m){}
    Matrix operator*(Matrix &A){
        Matrix B{n,A.m};
        for(int i{};i<n;i++){
            for(int j{};j<A.m;j++){
                for(int k{};k<m;k++){
                    B.a[i][j]=(B.a[i][j]+a[i][k]*A.a[k][j]%p)%p;
                }
            }
        }
        return B;
    }
};
Matrix qpow(Matrix A,int b){
    Matrix res{A.n,A.m};
    res.a[0][0]=1;res.a[1][1]=1;
    while(b>0){
        if(b&1)res=res*A;
        A=A*A;
        b>>=1ll;
    }
    return res;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;
    cin>>n;
    if(n==0){
        cout<<0<<"\n";
        return 0;
    }
    Matrix C{2,2};
    C.a[0][0]=1;C.a[0][1]=1;C.a[1][0]=1;C.a[1][1]=0;
    Matrix res=qpow(C,n-1);
    Matrix F{2,1};
    F.a[0][0]=1;
    F=res*F;
    cout<<F.a[0][0]<<"\n";
    cout.flush();
    return 0;
}