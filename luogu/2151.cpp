#include<iostream>
using namespace std;
const int maxm=60,maxn=50,P=45989;
int head[maxn*3][2]={},nxt[maxm*3][2]={},cnt=0;
struct Martix{
    int line,row;
    int martix[maxm*3][maxm*3];
    Martix():line(120),row(120),martix{}{}
    Martix(int _line,int _row):line(_line),row(_row),martix{}{}
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
            //cout<<'d';
            //cout<<(b*a).martix[1][(n-1)*9+1]<<endl;
            //cout<<'b';
            b=b*a;
            //cout<<'c';
            // pm(b);
        }
        a=a*a;
        t>>=1;     
    }
    return b;
}
void pm(Martix A){
    for(int i=1;i<=A.line;i++){
        for(int j=1;j<=A.row;j++){
            cout<<A.martix[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    int n,m,t,a,b;
    cin>>n>>m>>t>>a>>b;
    int x,y;
    Martix c(m*2,m*2);
    for(int i=1;i<=m;i++){
       cin>>x>>y;
       ++cnt;
       nxt[cnt][0]=head[x][0];
       head[x][0]=cnt;
       nxt[cnt][1]=head[y][1];
       head[y][1]=cnt;
       for(int e=head[x][1];e;e=nxt[e][1]){
           c.martix[e][cnt]=1;
       }
       for(int e=head[y][0];e;e=nxt[e][0]){
           c.martix[cnt][e]=1;
       }
       ++cnt;
       nxt[cnt][0]=head[y][0];
       head[y][0]=cnt;
       nxt[cnt][1]=head[x][1];
       head[x][1]=cnt;
       for(int e=head[y][1];e;e=nxt[e][1]){
           if(e!=cnt-1)c.martix[e][cnt]=1;
       }
       for(int e=head[x][0];e;e=nxt[e][0]){
           if(e!=cnt-1)c.martix[cnt][e]=1;
       }
    }
    pm(c);
    Martix res=mpow(c,1);
    pm(res);
    int ans=0;
    for(int e=head[a][0];e;e=nxt[e][0]){
        for(int u=head[b][1];u;u=nxt[u][1]){
            //cout<<e<<' '<<u;
            ans+=res.martix[e][u];
            ans%=P;
        }
    }
    cout<<ans<<endl;
    return 0;
}
