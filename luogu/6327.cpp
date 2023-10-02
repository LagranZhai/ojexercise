#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn{2e5};
int n,m;
double tsin[maxn*4],tcos[maxn*4];
int a[maxn*2],tag[maxn*2];
void build(int p,int cl,int cr){
    if(cl==cr){
        tsin[p]=std::sin(a[p]);
        tcos[p]=std::cos(a[p]);
        return ;
    }
    int mid=(cl+cr)/2;
    build(p*2,cl,mid);
    build(p*2+1,mid+1,cr);
    tsin[p]=tsin[p*2]+tsin[p*2+1];
    tcos[p]=tcos[p*2]+tcos[p*2+1];
    return ;
}
void update(int p,int cl,int cr,int l,int r,const int w){
    if(cl>=l&&cr<=r){
        double os=tsin[p],oc=tcos[p];
        tag[p]+=w;
        tsin[p]=std::sin(w)*oc+std::cos(w)*os;
        tcos[p]
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    cin>>m;

    return 0;
}