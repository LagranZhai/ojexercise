#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
#define int long long
constexpr int maxn=1e15,maxm=52,p=1e9+7;
struct Matrix{
    // int a[maxm+10][maxm+10]{{}};
    std::vector<std::vector<int> > a;
    int n{},m{};
    Matrix(const Matrix& A)=default;
    Matrix(int _a,int _b):n(_a),m(_b){
        a.resize(n+10,std::vector<int>(m+10,0));
    }
    static Matrix mul(const Matrix& A,const Matrix& B){
        Matrix C{A.n,B.m};
        for(int i{1};i<=C.n;i++){
            for(int j{1};j<=C.m;j++){
                for(int k{1};k<=A.m;k++){
                    C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%p)%p;
                }
            }
        }
        return C;
    }
    Matrix& operator=(const Matrix& A)=default;
    Matrix& operator=(Matrix&& A)noexcept{
        if(this!=&A){
            this->a=A.a;
            this->n=A.n;
            this->m=A.m;
        }
        return *this;
    }
};
void qpow(Matrix& C,Matrix A,int b){
    while(b>0){
        if(b&1)C=Matrix::mul(C,A);
        A=Matrix::mul(A,A);
        b>>=1;
    }
    return ;
}
inline int ctoi(char x){
    if(x-'a'<0){
        return x-'A'+27;
    }
    else{
        return x-'a'+1;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,k;
    cin>>n>>m>>k;
    char a,b;
    Matrix c{m,m};
    for(int i{1};i<=m;i++){
        for(int j{1};j<=m;j++){
            c.a[i][j]=1;
        }
    }
    for(int i{1};i<=k;i++){
        cin>>a>>b;
        c.a[ctoi(a)][ctoi(b)]=0;
    }
    Matrix ans{1,m};
    for(int i{1};i<=m;i++){
        ans.a[1][i]=1;
    }
    qpow(ans,c,n-1);
    int aans{0};
    for(int i{1};i<=m;i++){
        aans=(aans+ans.a[1][i])%p;
    }
    cout<<aans<<"\n";
    cout.flush();
    return 0;
}