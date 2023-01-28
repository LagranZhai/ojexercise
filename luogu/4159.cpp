#include<bits/stdc++.h>
using namespace std;
const int P=2009;
int n,t;
struct Martix{
    int line,row;
    int martix[201][201];
    Martix():line(0),row(0),martix(){cout<<'a';};
    Martix operator*(Martix A){
        Martix result;
        result.line=this->line;result.row=A.row;
        for(int i=1;i<=result.line;i++){
            for(int j=1;j<=result.row;j++){
                for(int k=1;k<=this->row;k++){
                    result.martix[i][j]+=this->martix[i][k]*A.martix[k][j];
                    result.martix[i][j]%=P;
                }
            }
        }
        return result;
    }
    // void operator=(Martix A){
    //     this->line=A.line;this->row=A.row;
    //     for(int i=1;i<=this->line;i++){
    //         for(int j=1;j<=this->row;j++){
    //             this->martix[i][j]=A.martix[i][j];
    //         }
    //     }
    //     return;
    // }
};
void pm(Martix A){
    for(int i=1;i<=A.line;i++){
        for(int j=1;j<=A.row;j++){
            cout<<A.martix[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}
Martix mpow(Martix a,int t){
    Martix b;b.line=a.line;b.row=a.row;
    for(int i=1;i<=b.line;i++){
        b.martix[i][i]=1;
    }
    while(t){   
        if(t&1){
            // cout<<"a="<<endl;
            // pm(a);
            // cout<<"b="<<endl;
            // pm(b);
            // cout<<"b*a="<<endl;
            cout<<'d';
            cout<<(b*a).martix[1][(n-1)*9+1]<<endl;
            cout<<'b';
            b=b*a;
            cout<<'c';
            // pm(b);
        }
        a=a*a;
        t>>=1;     
    }
    return b;
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>t;
    Martix c;c.line=9*n;c.row=9*n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=8;j++){
            c.martix[(i-1)*9+j][(i-1)*9+j+1]=1;
        }
    }
    //cout<<'a'<<endl;
    long long s;
    for(int i=1;i<=n;i++){
        cin>>s;
        for(int j=n;j>=1;j--){
            //cout<<s%10<<' ';
            if(s%10!=0)c.martix[(i-1)*9+(int)(s%10)][(j-1)*9+1]=1;
            s/=10;
        }
        //cout<<endl;
    }
    Martix res=mpow(c,t);
    cout<<res.martix[1][(n-1)*9+1]<<endl;
    return 0;
}