#include<bits/stdc++.h>
using std::cin,std::cout,std::ios;
constexpr int maxn=1e6;
int st[maxn+100][22],mylog[maxn+100];
void init(int n){
    mylog[0]=mylog[1]=0;
    for(int i{2};i<=n;i++){
        mylog[i]=mylog[i/2]+1;
    }
    int len{mylog[n]};
    for(int l{1};l<=len;l++){
        for(int i{1};i+(1<<l)-1<=n;i++){
            int j{1<<(l-1)};
            st[i][l]=std::max(st[i][l-1],st[i+j][l-1]);
        }
    }
}
int query(int l,int r){
    int len{mylog[r-l+1]};
    return std::max(st[l][len],st[r-(1<<len)+1][len]);
}
int a[maxn*2];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    
    for(int i{1};i<=n;i++){
        cin>>st[i][0];
    }
    init(n);
    int l,r;
    for(int i{1};i<=n;i++){
        int a=
    }
    // for(int i{1};i<=m;i++){
    //     cin>>l>>r;
    //     cout<<query(l,r)<<"\n";
    // }
    cout<<std::flush;
    return 0;
}