#include<bits/stdc++.h>
using std::cin,std::cout,std::cerr;
#define int long long
#define double long double
double s2=sqrt(2);
// double eps=1e-10;
auto drop(double &t,double &h){
    if(h/2.0<0.000001){
        return ;
    }
    double t1{2.0*sqrt(0.1*h)};
    h/=2.0;
    if(t>t1){
        t-=t1;
        drop(t,h);
        return ;
    }
    else{
        double v0{sqrt(20.0*h)};
        h=v0*t-5.0*t*t;
        return ;
    }
}
signed main(){
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    cout<<std::fixed<<std::setprecision(2);
    while(T--){
        double h,t;
        cin>>h>>t;
        double t0{sqrt(0.2*h)};
        if(t<t0){
            cout<<h-5.0*t*t<<"\n";
        }
        else{
            t-=t0;
            drop(t,h);
            cout<<h<<"\n";    
        }
    }
    cout.flush();
    return 0;
}