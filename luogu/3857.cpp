#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::ios;
constexpr int maxn=50,maxw=50,P=2008;
#define int long long
int a[maxn*2];
int d[maxn*2];
int n,m;
void insert(int x){
    for(int i{maxw};i>=0;i--){
        if(x&(1ll<<i)){
            if(d[i]){
                x^=d[i];
            }
            else{
                d[i]=x;
                break;
            }
        }
    }
}
int qpow(int a,int b){
    int c{1};
    while(b>0){
        if(b&1)c=c*a%P;
        a=a*a%P;
        b>>=1;
    }
    return c;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    std::string s;
    for(int i{1};i<=m;i++){
        cin>>s;
        int base{1};
        int tmp{0};
        for(int i{0};i<s.size();i++){
            if(s[i]=='O')tmp+=base;
            base<<=1;
        }
        insert(tmp);
    }
    int cnt{0};
    for(int i{maxw};i>=0;i--){
        if(d[i])cnt++;
    }
    cout<<qpow(2,cnt)<<"\n";
    cout.flush();
    return 0;
}