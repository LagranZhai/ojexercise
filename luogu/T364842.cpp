#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<type_traits>
#include<functional>
#include<queue>
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
constexpr int maxn=1e6;
int a[maxn+100];
std::vector<int > q;
int n;
std::tuple<bool,int,int > check(int l){
    for(int i{q.size()-l};i<q.size();i++){
        a[q[i]]=-1;
    }
    int sum=1,cnt=1;
    bool flag=1;
    for(int i{1};i<=n;i++){
        if(a[i]==1||a[i]==0){
            sum+=1;
            cnt+=1;
        }
        else if(a[i]==-1){
            if(cnt<2){
                flag=0;
                break;
            }
            cnt-=1;
        }
    }
    for(int i{q.size()-l};i<q.size();i++){
        a[q[i]]=0;
    }
    return std::make_tuple(flag,sum,cnt);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        q.clear();
        std::fill(a,a+maxn+100,0);
        for(int i{1};i<=n;i++){
            cin>>a[i];
            if(a[i]==0)q.push_back(i);
        }
        int l=0,r=q.size(),mid=(l+r)/2;
        int ans=0;
        while(l<=r){
            mid=(l+r)/2;
            auto t=check(mid);
            if(std::get<0>(t)){
                ans=mid;
                l=mid+1; 
            }
            else{
                r=mid-1;
            }
        }

        auto t=check(ans);
        if(std::get<0>(t)==0){
            cout<<-1<<"\n";
        }
        else{
            int gcd=std::__gcd(std::get<1>(t),std::get<2>(t));
            cout<<std::get<1>(t)/gcd<<" "<<std::get<2>(t)/gcd<<"\n";
        }
    }
    
    cout.flush();
    return 0;
}
