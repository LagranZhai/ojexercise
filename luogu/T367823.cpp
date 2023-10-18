#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
using std::cin,std::ios,std::max,std::min;
template<typename T>
struct Myos{
    T mys;
    Myos(T&& _s)noexcept:mys(
        std::forward<T>(_s)
    ) {}
    Myos<T>& flush() {
        mys<<std::flush;
        return *this;
    }
    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept {
        mys<<std::forward<Traits>(value);
        return *this;
    }
    ~Myos() {
        flush();
    }
};
template<> Myos<std::ostringstream>& Myos<std::ostringstream>::flush() {
        std::cout<<mys.str()<<std::flush;
        mys.str("");
        return *this;
}
//Myos<std::ostream&> cout{std::cout};
Myos<std::ostringstream> cout{std::ostringstream()};
constexpr int maxn=12;
int n;
int a[maxn+100],b[maxn+100],maxa=0;
bool checkk(){
    int k=1;
    while(b[k]<=b[k+1]&&k<n)k++;
    while(b[k]>=b[k+1]&&k<n)k++;
    if(k==n){
        // for(int i{1};i<=n;i++)cout<<b[i]<<" ";
        return 1;
    }
    else return 0;
}
bool rv(int x){
    if(x>0){
        for(int i{1};i<n;i++){
            std::swap(b[i],b[i+1]);
            if(rv(x-1))return 1;
            std::swap(b[i],b[i+1]);
        }
    }
    else{
        if(checkk())return 1;
    }
    return 0;
}
bool check(int m){
    std::copy(std::begin(a),std::end(a),std::begin(b));
    return rv(m);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    for(int i{1};i<=n;i++){
        cin>>a[i];
        maxa=max(maxa,a[i]);
    }
    int l=0,r=n*n,mid=(l+r)/2,ans=0;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    // check(2);
    cout<<ans<<"\n";
    cout.flush();
    return 0;
}
