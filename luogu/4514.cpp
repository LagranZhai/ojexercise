#include<bits/stdc++.h>
using namespace std;
const int maxn=2048;
// struct BIT{
//     int a[maxn*2],n;
//     int lowbit(int x)const{
//         return x&(-x);
//     }
//     void single_update(int i,int d){
//         while(i<=n){
//             a[i]+=d;
//             i+=lowbit(i);
//         }
//         return;
//     }
//     int single_query(int i)const{
//         int ans=0;
//         while(i>0){
//             ans+=a[i];
//             i-=lowbit(i);
//         }
//         return ans;
//     }
//     void update(int x,int y,int d){
//         single_update(x,d);single_update(y+1,-d);
//         return;
//     }
//     int query(int x,int y)const{
//         return single_query(y)-single_query(x-1);
//     }
// };
struct diBIT{
    int a[maxn*2][maxn*2],n=0,m=0;
    diBIT(int _n,int _m):n(_n),m(_m),a{}{}
    diBIT(const diBIT &other):a(other.a),n(other.n),m(other.m){}
    int lowbit(int x)const{
         return x&(-x);
    }
    void single_update(int x,int y,int d){
        while(x<=n){
            while(y<=m){
                a[x][y]+=d;
                y+=lowbit(y);
            }
            x+=lowbit(x);
        }
        return;
    }
    int single_query(int i)const{
        int ans=0;
        while(i>0){
            ans+=a[i];
            i-=lowbit(i);
        }
        return ans;
    }
    void update(int x,int y,int d){
        single_update(x,d);single_update(y+1,-d);
        return;
    }
    int query(int x,int y)const{
        return single_query(y)-single_query(x-1);
    }
}
void multiupdate(BIT t,int a,int b,int c,int d,int delta){

}
int n,m;
int main(){
    ios::sync_with_stdio(false);
    char opt;
    cin>>opt>>n>>m;
    int a,b,c,d,delta;
    while(cin>>opt){
        if(opt=='L'){
            cin>>a>>b>>c>>d>>delta;

        }
        else{
            cin>>a>>b>>c>>d;
        }
    }
    return 0;
}