#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5;
int n,m,a[maxn*2];
struct Martix{
    int a,b,martix[4][4];
    Martix operator*(Martix A){
        Martix c;
        c.a=a;c.b=A.b;
        for(int i=1;i<=c.a;i++){
            for(int j=1;j<=c.b;j++){
                if(martix[i][1]==-2e9||A.martix[1][j]==-2e9)c.martix[i][j]=-2e9;
                else c.martix[i][j]=martix[i][1]+A.martix[1][j];
                for(int k=2;k<=b;k++){
                    if(martix[i][k]==-2e9||A.martix[k][j]==-2e9)continue;
                    c.martix[i][j]=max(c.martix[i][j],martix[i][k]+A.martix[k][j]);
                }
            }
        }
        return c;
    }
}mar[maxn*2],tree[maxn*4+100];
void build(int cl, int cr,int p){
    if(cl==cr){
        tree[p]=mar[cl];
        return;
    }
    int mid=(cl+cr)/2;
    build(cl,mid,p*2);
    build(mid+1,cr,p*2+1);
    tree[p]=tree[p*2]*tree[p*2+1];
    return;
}
void update(int l,int cl,int cr,int p,Martix d){
    if(cl==cr){
        tree[p]=d;
        return;
    }
    int mid=(cl+cr)/2;
    if(l<=mid)update(l,cl,mid,p*2,d);
    if(l>mid)update(l,mid+1,cr,p*2+1,d);
    tree[p]=tree[p*2]*tree[p*2+1];
    return;
}
Martix query(int l,int r,int cl,int cr,int p){
    if(cl>=l&&cr<=r){
        return tree[p];
    }
    int mid=(cl+cr)/2;
    Martix a,b;
    if(r<=mid)return query(l,r,cl,mid,p*2);
    if(l>mid)return query(l,r,mid+1,cr,p*2+1);
    if(l<=mid)a=query(l,r,cl,mid,p*2);
    if(r>mid)b=query(l,r,mid+1,cr,p*2+1);
    return a*b;
}
void pm(Martix A){
    for(int i=1;i<=A.a;i++){
        for(int j=1;j<=A.b;j++){
            cout<<A.martix[i][j]<<' ';
        }
        cout<<endl;
    }
}
int main(){
    ios::sync_with_stdio(false);
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=n;i>=1;i--){
        mar[n-i+1].a=3;mar[n-i+1].b=3;
        mar[n-i+1].martix[1][1]=
        mar[n-i+1].martix[1][3]=
        mar[n-i+1].martix[2][1]=
        mar[n-i+1].martix[2][3]=a[i];
        mar[n-i+1].martix[2][2]=
        mar[n-i+1].martix[3][3]=0;
        mar[n-i+1].martix[1][2]=
        mar[n-i+1].martix[3][1]=
        mar[n-i+1].martix[3][2]=-2e9;
    }
    build(1,n,1);
    int l,r,k;
    Martix c;c.a=3;c.b=1;c.martix[1][1]=0;c.martix[2][1]=-1e9;c.martix[3][1]=0;
    while(m--){
        cin>>k;
        if(k==1){
            cin>>l>>r;
            if(l>r)swap(l,r);
            Martix a=query(n-r+1,n-l+1,1,n,1)*c;
           //pm(query(n-r+1,n-l+1,1,n,1));
          cout<<a.martix[2][1]<<endl;
        }
        else{
            cin>>l>>r;
            Martix m;
            m.a=3;m.b=3;
            m.martix[1][1]=
            m.martix[1][3]=
            m.martix[2][1]=
            m.martix[2][3]=r;
            m.martix[2][2]=
            m.martix[3][3]=0;
            m.martix[1][2]=
            m.martix[3][1]=
            m.martix[3][2]=-2e9;
            update(n-l+1,1,n,1,m);
        }
    }
    return 0;
}