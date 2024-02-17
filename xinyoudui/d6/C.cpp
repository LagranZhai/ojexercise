//PC
#include<bits/stdc++.h>
using std::cin,std::cout,std::ios,std::cerr;
// #define int long long
using ll=long long;
constexpr int maxn=5e6+100,base=131,p1=1e9+7,p2=1e9+9;
std::string s;
struct Hash{
    int a1,a2;
    Hash()=default;
    Hash operator+(const Hash& B){
        return {(a1+B.a1)%p1,(a2+B.a2)%p2};
    }
    Hash operator*(const Hash& B){
        return {(ll)a1*B.a1%p1,(ll)a2*B.a2%p2};
    }
    Hash operator*(const int& B){
        return {(ll)a1*B%p1,(ll)a2*B%p2};
    }
    Hash operator-(const Hash& B){
        return {(a1-B.a1+p1)%p1,(a2-B.a2+p2)%p2};
    }
    bool operator==(const Hash& B){
        return (a1==B.a1)&&(a2==B.a2);
    }
}sum[maxn],power[maxn],suf[maxn];
Hash get1(int l,int r){
    return sum[r]-sum[l-1]*power[r-l+1];
}
Hash get2(int l,int r){
    return suf[l]-suf[r+1]*power[r-l+1];
}
int deg[maxn]{0};
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>s;
    power[0]={1,1};
    for(int i{1};i<=s.size();i++){
        power[i]=power[i-1]*base;
    }
    sum[0]={0,0};
    for(int i{1};i<=s.size();i++){
        sum[i]=sum[i-1]*base+Hash{(int)s[i-1],(int)s[i-1]};
    }
    suf[s.size()+1]={0,0};
    for(int i{s.size()};i>=1;i--){
        suf[i]=suf[i+1]*base+Hash{(int)s[i-1],(int)s[i-1]};
    }
    deg[0]=0;deg[1]=1;
    int ans{1};
    for(int i{2};i<=s.size();i++){
        // cout<<sum[i].a1<<"\n";
        if(get1(1,i/2)==get2(i-i/2+1,i)){
            deg[i]=deg[i/2]+1;
            ans+=deg[i];
        }
        // cout<<deg[i]<<"\n";
    }
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}